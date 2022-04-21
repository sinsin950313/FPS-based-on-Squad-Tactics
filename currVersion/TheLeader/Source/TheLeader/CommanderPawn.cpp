// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderPawn.h"
#include "Camera\CameraComponent.h"
#include "TheLeaderPlayerController.h"
#include "TheLeaderCommonData.h"
#include "GameFramework/PawnMovementComponent.h" 
#include "Components/SphereComponent.h" 

const FName ACommanderPawn::kFireAttitude(TEXT("FireAttitude"));

// Sets default values
ACommanderPawn::ACommanderPawn()
{
	SetPlayMode(EPlayerMode::COMMODE);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMeshComponent()->SetVisibility(false);

	MovementComponent->SetUpdatedComponent(RootComponent);

	_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	_cameraComponent->SetupAttachment(RootComponent);
	_cameraComponent->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ACommanderPawn::BeginPlay()
{
	Super::BeginPlay();

	AFPSPawn* member = GetWorld()->SpawnActor<AFPSPawn>(GetActorLocation() - FVector(0, 0, 0), GetActorRotation());
	_squadMembers.Add(Cast<AFPSAIController>(member->GetController()));

	member = GetWorld()->SpawnActor<AFPSPawn>(GetActorLocation() - FVector(100, 0, 0), GetActorRotation());
	_squadMembers.Add(Cast<AFPSAIController>(member->GetController()));
}

void ACommanderPawn::DoIterateToMembers(TFunction<void(IFireable*)> doFunction)
{
	IFireable* fireable;
	if (_currentLeader != nullptr && !_currentLeader->IsActorBeingDestroyed())
	{
		ATheLeaderPlayerController* controller = Cast<ATheLeaderPlayerController>(_currentLeader->GetController());
		if (controller != nullptr)
		{
			fireable = Cast<IFireable>(controller);
			doFunction(fireable);
		}
	}

	for (auto& member : _squadMembers)
	{
		fireable = Cast<IFireable>(member);
		doFunction(fireable);
	}
}

AFPSPawn* ACommanderPawn::GetLeader()
{
	if (_currentLeader == nullptr || _currentLeader->IsActorBeingDestroyed())
	{
		AFPSAIController* controller = *_squadMembers.begin();
		_currentLeader = Cast<AFPSPawn>(controller->GetPawn());
		_squadMembers.Remove(controller);
	}
	return _currentLeader;
}

// Called every frame
void ACommanderPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoIterateToMembers([](IFireable* fireable)->void { fireable->IsAttack(); });
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
		UE_LOG(LogTemp, Log, TEXT("To FPS Mode"));
		currController->ChangePlayMode(GetPlayMode());
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
	}
}

void ACommanderPawn::ChangeSquadFireAttitude(EBotFireAttitude attitude)
{
	_currentFireAttitude = attitude;
	DoIterateToMembers([attitude](IFireable* fireable)->void { fireable->SetFireAttitude(attitude); });
}

EBotFireAttitude ACommanderPawn::GetSquadFireAttitude()
{
	return _currentFireAttitude;
}
