// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TheLeaderPlayerController.h"
#include "TheLeaderCommonData.h"
#include "FPSAIController.h"
#include "ProjectileActor.h"

// Sets default values
AFPSPawn::AFPSPawn()
{
	SetPlayMode(EPlayerMode::FPSMODE);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	_cameraComponent->SetupAttachment(RootComponent);
	_cameraComponent->AddRelativeLocation(FVector(0.0f, 0.0f, 44.0f));
	_cameraComponent->bUsePawnControlRotation = true;

	_currentState = EState::STANDUP;

	AIControllerClass = AFPSAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	UStaticMeshComponent* meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComponent->SetupAttachment(RootComponent);
	AddOwnedComponent(meshComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
	}

	_lastAttackTime = _coolTime;
}

// Called when the game starts or when spawned
void AFPSPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	_lastAttackTime += DeltaTime;

	if (_bAttackStart)
	{
		if (_coolTime <= _lastAttackTime)
		{
			Fire();
		}
	}
}

// Called to bind functionality to input
void AFPSPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AFPSPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Backward"), this, &AFPSPawn::MoveBackward);
	PlayerInputComponent->BindAxis(TEXT("RightSide"), this, &AFPSPawn::MoveRightSide);
	PlayerInputComponent->BindAxis(TEXT("LeftSide"), this, &AFPSPawn::MoveLeftSide);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFPSPawn::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookAt"), this, &AFPSPawn::LookAt);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AFPSPawn::AttackStart);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &AFPSPawn::AttackStop);

	PlayerInputComponent->BindAction(TEXT("Kneel"), EInputEvent::IE_Pressed, this, &AFPSPawn::Kneel);

	PlayerInputComponent->BindAction(TEXT("ToCommand"), EInputEvent::IE_Pressed, this, &AFPSPawn::ToCommandMode);
}

void AFPSPawn::MoveForward(float val)
{
	AddMovementInput(GetActorForwardVector(), val * GetCurrentMovementCoefficient());
}

void AFPSPawn::MoveBackward(float val)
{
	AddMovementInput(GetActorForwardVector(), val * GetCurrentMovementCoefficient());
}

void AFPSPawn::MoveLeftSide(float val)
{
	AddMovementInput(GetActorRightVector(), val * GetCurrentMovementCoefficient());
}

void AFPSPawn::MoveRightSide(float val)
{
	AddMovementInput(GetActorRightVector(), val * GetCurrentMovementCoefficient());
}

void AFPSPawn::Turn(float val)
{
	AddControllerYawInput(val);
}

void AFPSPawn::LookAt(float val)
{
	AddControllerPitchInput(-val);
}

void AFPSPawn::AttackStart()
{
	_bAttackStart = true;
}

void AFPSPawn::AttackStop()
{
	_bAttackStart = false;
}

void AFPSPawn::Kneel()
{
	if (_currentState != EState::KNEEL)
	{
		SetState(EState::KNEEL);
	}
	else
	{
		SetState(EState::STANDUP);
	}
}

void AFPSPawn::ToCommandMode()
{
	ATheLeaderPlayerController* currController = Cast<ATheLeaderPlayerController>(GetController());
	if (currController != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("To Command Mode"));
		currController->ChangePlayMode(GetPlayMode());
	}
}

void AFPSPawn::Fire()
{
	GetWorld()->SpawnActor<AProjectileActor>(_cameraComponent->GetComponentLocation() + _cameraComponent->GetForwardVector() * 100, _cameraComponent->GetComponentRotation());
	_lastAttackTime = 0;

	UE_LOG(LogTemp, Log, TEXT("Call Fire Attitude Delegate execute"));
	FireAttitudeDelegate.ExecuteIfBound();
}

void AFPSPawn::SetState(EState state)
{
	if (_currentState != EState::PINNED)
	{
		switch (state)
		{
		case AFPSPawn::EState::STANDUP:
			UE_LOG(LogTemp, Log, TEXT("Stand Up"));
			_currentState = EState::STANDUP;
			break;
		case AFPSPawn::EState::KNEEL:
			UE_LOG(LogTemp, Log, TEXT("Kneel"));
			_currentState = EState::KNEEL;
			break;
		case AFPSPawn::EState::PINNED:
			UE_LOG(LogTemp, Log, TEXT("Pinned"));
			_currentState = EState::PINNED;
			break;
		default:
			break;
		}
	}
}

float AFPSPawn::GetCurrentMovementCoefficient()
{
	float returnVal = 0.0f;

	switch (_currentState)
	{
	case AFPSPawn::EState::STANDUP:
		returnVal = _kStandUpStateCoefficient;
		break;
	case AFPSPawn::EState::KNEEL:
		returnVal = _kKneelStateCoefficient;
		break;
	case AFPSPawn::EState::PINNED:
		returnVal = _kPinnedStateCoefficient;
		break;
	default:
		break;
	}

	return returnVal;
}
