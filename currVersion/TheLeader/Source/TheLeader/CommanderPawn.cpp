// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderPawn.h"
#include "Camera\CameraComponent.h"
#include "TheLeaderPlayerController.h"
#include "TheLeaderCommonData.h"
#include "GameFramework/PawnMovementComponent.h" 
#include "Components/SphereComponent.h" 
#include "BehaviorTree/BlackboardComponent.h" 

const FName ACommanderPawn::kFireAttitude(TEXT("FireAttitude"));

// Sets default values
ACommanderPawn::ACommanderPawn() : _mode(EPlayerMode::COMMODE)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMeshComponent()->SetVisibility(false);

	MovementComponent->SetUpdatedComponent(RootComponent);

	_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	_cameraComponent->SetupAttachment(RootComponent);
	_cameraComponent->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

	_squadSharedData = new SquadSharedData();
}

ACommanderPawn::~ACommanderPawn()
{
	delete _squadSharedData;
}

void ACommanderPawn::SetDirection(float yawVal)
{
	FRotator rotation = RootComponent->GetComponentRotation();
	rotation.Yaw = yawVal;
	RootComponent->SetWorldRotation(rotation);
}

// Called when the game starts or when spawned
void ACommanderPawn::BeginPlay()
{
	Super::BeginPlay();

	CreateMember(FVector(0, 0, 0));
	CreateMember(FVector(-300, 0, 0));

	ATheLeaderPlayerController* controller = Cast<ATheLeaderPlayerController>(GetController());
	controller->SetSquadSharedData(_squadSharedData);

	ToFPSMode();
}

void ACommanderPawn::CreateMember(FVector relativeLocation)
{
	APositionPointer* pointer = GetWorld()->SpawnActor<APositionPointer>(GetActorLocation() + relativeLocation, FRotator());
	pointer->SetRelativeLocation(relativeLocation);
	_positionPointers.Add(pointer);

	AFPSPawn* member = GetWorld()->SpawnActor<AFPSPawn>(pointer->GetActorLocation(), GetActorRotation());
	member->SetActorHiddenInGame(false);

	AFPSAIController* controller = Cast<AFPSAIController>(member->GetController());
	member->FireAttitudeDelegate.BindUFunction(controller, FName("SetFireAttitude"));
	_squadMembers.Add(Cast<AFPSAIController>(member->GetController()));

	controller->SetPosition(pointer);

	ControllerBuilder::GetInstance()
		->InitTeam(ETeam::PLAYER)
		->SharedDataSet(_squadSharedData)
		->Build(controller);
}

template<typename ToLeader, typename ToMembers>
void ACommanderPawn::DoIterateToMembers(ToLeader doFunctionWithLeader, ToMembers doFunctionWithMembers)
{
	doFunctionWithLeader(this, GetLeader());

	for (auto& member : _squadMembers)
	{
		doFunctionWithMembers(member);
	}
}

AFPSPawn* ACommanderPawn::GetLeader()
{
	if (_currentLeader == nullptr || _currentLeader->IsActorBeingDestroyed())
	{
		AFPSAIController* controller = *_squadMembers.begin();
		_currentLeader = Cast<AFPSPawn>(controller->GetPawn());
		_currentLeader->FireAttitudeDelegate.BindUFunction(controller, FName("SetFireAttitude"));
		_squadMembers.Remove(controller);
		controller->Destroy();

		APositionPointer* temp = *_positionPointers.begin();
		_positionPointers.Remove(temp);
		temp->Destroy();
	}
	return _currentLeader;
}

// Called every frame
void ACommanderPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool isFire = false;
	DoIterateToMembers(
		[&isFire](ACommanderPawn* commander, AFPSPawn* leader)-> void {
			ATheLeaderPlayerController* controller = Cast<ATheLeaderPlayerController>(commander->GetController());
			if (controller == nullptr)
			{
				controller = Cast<ATheLeaderPlayerController>(leader->GetController());
			}

			if (controller != nullptr)
			{
				isFire |= (controller->GetFireAttitude() == EBotFireAttitude::FIREATWILL);
			}
		},
		[&isFire](AFPSAIController* controller)-> void {
			isFire |= (controller->GetFireAttitude() == EBotFireAttitude::FIREATWILL);
		});

	if (GetSquadFireAttitude() == EBotFireAttitude::HOLDFIRE && isFire)
	{
		SetSquadFireAttitude(EBotFireAttitude::FIREATWILL);
	}

	UpdateFormation();
}

// Called to bind functionality to input
void ACommanderPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//removed for overlapped command like 'e'
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ACommanderPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Backward"), this, &ACommanderPawn::MoveBackward);
	PlayerInputComponent->BindAxis(TEXT("RightSide"), this, &ACommanderPawn::MoveRightSide);
	PlayerInputComponent->BindAxis(TEXT("LeftSide"), this, &ACommanderPawn::MoveLeftSide);

	PlayerInputComponent->BindAxis(TEXT("Command Turn"), this, &ACommanderPawn::Turn);

	PlayerInputComponent->BindAction(TEXT("ToFPS"), EInputEvent::IE_Pressed, this, &ACommanderPawn::ToFPSMode);

	PlayerInputComponent->BindAction(TEXT("ToMove"), EInputEvent::IE_Pressed, this, &ACommanderPawn::ToMove);
	PlayerInputComponent->BindAction(TEXT("LookAt"), EInputEvent::IE_Released, this, &ACommanderPawn::LookAt);

	PlayerInputComponent->BindAction(TEXT("FireAtWill"), EInputEvent::IE_Pressed, this, &ACommanderPawn::FireAtWill);
	PlayerInputComponent->BindAction(TEXT("HoldFire"), EInputEvent::IE_Pressed, this, &ACommanderPawn::HoldFire);
	PlayerInputComponent->BindAction(TEXT("Return To Formation"), EInputEvent::IE_Pressed, this, &ACommanderPawn::ReturnToFormation);
}

void ACommanderPawn::MoveForward(float val)
{
	FVector forward = GetActorForwardVector();
	forward.Z = 0;
	forward.Normalize();
	AddMovementInput(forward, val);
}

void ACommanderPawn::MoveBackward(float val)
{
	FVector forward = GetActorForwardVector();
	forward.Z = 0;
	forward.Normalize();
	AddMovementInput(forward, val);
}

void ACommanderPawn::MoveLeftSide(float val)
{
	FVector right = GetActorRightVector();
	right.Z = 0;
	right.Normalize();
	AddMovementInput(right, val);
}

void ACommanderPawn::MoveRightSide(float val)
{
	FVector right = GetActorRightVector();
	right.Z = 0;
	right.Normalize();
	AddMovementInput(right, val);
}

void ACommanderPawn::Turn(float val)
{
	RootComponent->AddRelativeRotation(FRotator(0.0f, val, 0.0f));
}

void ACommanderPawn::ToFPSMode()
{
	ATheLeaderPlayerController* currController = Cast<ATheLeaderPlayerController>(GetController());
	if (currController != nullptr)
	{
		currController->ChangePlayMode(_mode);
	}
}

void ACommanderPawn::ToMove()
{
	APlayerController* controller = Cast<APlayerController>(GetController());
	if (controller != nullptr)
	{
		FHitResult hit;
		controller->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel3, false, hit);
		UE_LOG(LogTemp, Log, TEXT("%s"), *hit.Location.ToString());
		//DoIterateToMembers(
		//	[](ACommanderPawn* commander, AFPSPawn* leader)->void {
		//		//do nothing
		//	},
		//	[hit](AFPSAIController* controller)->void {
		//		//controller->MoveToDestination(hit.Location);
		//	});
		for (auto iter = _positionPointers.CreateIterator(); iter; ++iter)
		{
			_positionPointers[iter.GetIndex()]->SetPinPosition(hit.Location);
		}
	}
}

void ACommanderPawn::LookAt()
{
	APlayerController* controller = Cast<APlayerController>(GetController());
	if (controller != nullptr)
	{
		FHitResult hit;
		controller->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel3, false, hit);
		DoIterateToMembers(
			[](ACommanderPawn* commander, AFPSPawn* leader)->void
			{
				//do nothing
			},
			[hit](AFPSAIController* controller)->void
			{
				controller->LookAt(hit.Location);
			});
	}
}

void ACommanderPawn::FireAtWill()
{
	UE_LOG(LogTemp, Log, TEXT("Fire At Will"));
	SetSquadFireAttitude(EBotFireAttitude::FIREATWILL);
}

void ACommanderPawn::HoldFire()
{
	UE_LOG(LogTemp, Log, TEXT("Hold Fire"));
	SetSquadFireAttitude(EBotFireAttitude::HOLDFIRE);
}

void ACommanderPawn::SetSquadFireAttitude(EBotFireAttitude attitude)
{
	_currentFireAttitude = attitude;
	DoIterateToMembers(
		[attitude](ACommanderPawn* commander, AFPSPawn* leader)->void {
			ATheLeaderPlayerController* controller = Cast<ATheLeaderPlayerController>(commander->GetController());
			if (controller == nullptr)
			{
				controller = Cast<ATheLeaderPlayerController>(leader->GetController());
			}
			if (controller != nullptr)
			{
				controller->SetFireAttitude(attitude);
			}
		},
		[attitude](AFPSAIController* controller)->void {
			controller->SetFireAttitude(attitude);
		});
}

EBotFireAttitude ACommanderPawn::GetSquadFireAttitude()
{
	return _currentFireAttitude;
}

void ACommanderPawn::UpdateFormation()
{
	for (auto iter = _positionPointers.CreateIterator(); iter; ++iter)
	{
		_positionPointers[iter.GetIndex()]->SetDestination(GetLeader()->GetActorLocation());
	}
}

void ACommanderPawn::ReturnToFormation()
{
	for (auto iter = _positionPointers.CreateIterator(); iter; ++iter)
	{
		_positionPointers[iter.GetIndex()]->GetBackToFormation();
	}
}
