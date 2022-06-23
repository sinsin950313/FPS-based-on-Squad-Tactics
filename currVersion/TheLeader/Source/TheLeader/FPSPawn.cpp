// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TheLeaderPlayerController.h"
#include "TheLeaderCommonData.h"
#include "FPSAIController.h"
#include "ProjectileActor.h"
#include "Interface/InGameControllerInterface.h"

// Sets default values
AFPSPawn::AFPSPawn() : _mode(EPlayerMode::FPSMODE)
{
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

	SetActorHiddenInGame(true);

	_lastAttackTime = _coolTime;

	//I think character has default sight
	//_stimuliComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliComponent"));
	//_stimuliComponent->RegisterForSense(UAISense_Sight::StaticClass());

	UStaticMeshComponent* moraleArea = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Morale Area"));
	moraleArea->SetVisibility(false);
	moraleArea->SetWorldScale3D(FVector(3, 3, 3));
	moraleArea->SetupAttachment(RootComponent);
	AddOwnedComponent(moraleArea);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> moraleAreaMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (moraleAreaMesh.Succeeded())
	{
		moraleArea->SetStaticMesh(moraleAreaMesh.Object);
	}
	moraleArea->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel5);
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

	Fire();

	MoraleRecoveryCheck();

	MoraleRecovery();

	if (_bShow)
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), IsHidden() ? TEXT("True") : TEXT("False"));
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
		currController->ChangePlayMode(_mode);
	}
}

void AFPSPawn::Fire()
{
	if (_bAttackStart)
	{
		if (_coolTime <= _lastAttackTime)
		{
			FActorSpawnParameters param;
			param.Instigator = this;
			GetWorld()->SpawnActor<AProjectileActor>(_cameraComponent->GetComponentLocation() + _cameraComponent->GetForwardVector() * 100, _cameraComponent->GetComponentRotation(), param);
			_lastAttackTime = 0;

			UE_LOG(LogTemp, Log, TEXT("Call Fire Attitude Delegate execute"));
			FireAttitudeDelegate.ExecuteIfBound(EBotFireAttitude::FIREATWILL);
		}
	}
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

float AFPSPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float finalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Log, TEXT("Final Damage : %f"), finalDamage);
	_HP -= finalDamage;
	UE_LOG(LogTemp, Log, TEXT("Remain HP : %d"), _HP);

	if (_HP <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Unit Dead"));
		Destroy();
	}

	return finalDamage;
}

float AFPSPawn::GetCurrentTime()
{
	return GetWorld()->GetTimeSeconds();
}

void AFPSPawn::MoraleAttack(APawn* attacker, int moraleDamage)
{
	AFPSPawn* attackerPawn = Cast<AFPSPawn>(attacker);
	IInGameControllerInterface* attackerController = Cast<IInGameControllerInterface>(attackerPawn->GetController());
	if (attackerController == nullptr)
	{
		return;
	}
	IInGameControllerInterface* thisController = Cast<IInGameControllerInterface>(GetController());
	if (thisController == nullptr)
	{
		return;
	}

	if (attackerController->GetGenericTeamId() != thisController->GetGenericTeamId())
	{
		_morale = ((_morale - moraleDamage) < _minMorale) ? _minMorale : (_morale - moraleDamage);
		_lastMoraleDamagedTime = GetCurrentTime();
		_bMoraleRecoveryStart = false;
	}
}

void AFPSPawn::MoraleRecoveryCheck()
{
	if (_moraleRecoveryStartInterval < GetCurrentTime() - _lastMoraleDamagedTime)
	{
		_bMoraleRecoveryStart = true;
	}
}

void AFPSPawn::MoraleRecovery()
{
	if (_bMoraleRecoveryStart)
	{
		float currentTime = GetCurrentTime();
		if (_lastMoraleRecoveryTime + _moraleRecoveryInterval < currentTime)
		{
			_morale = (_morale + _moraleRecoveryValue < 100) ? (_morale + _moraleRecoveryValue) : _maxMorale;
			_lastMoraleRecoveryTime = currentTime;
		}

		if (_morale == _maxMorale)
		{
			_bMoraleRecoveryStart = false;
		}
	}
}
