// Fill out your copyright notice in the Description page of Project Settings.


#include "TheLeaderPlayerController.h"
#include "CommanderPawn.h"
#include "ControllerBuilder.h"

ATheLeaderPlayerController::ATheLeaderPlayerController()
{
	Init();

	ControllerBuilder::GetInstance()
		->InitTeam(ETeam::PLAYER)
		->SharedDataSet(nullptr)
		->Build(this);
}

void ATheLeaderPlayerController::BeginPlay()
{
	Super::BeginPlay();

	_commandModePawn = Cast<ACommanderPawn>(GetPawn());
}

void ATheLeaderPlayerController::SetMouseEnable(bool enable)
{
	bEnableMouseOverEvents = enable;
	bShowMouseCursor = enable;
}

void ATheLeaderPlayerController::Init()
{
	_fireAttitude = CreateDefaultSubobject<UFireAttitude>(TEXT("Fire Attitude"));
	_teamAgent = CreateDefaultSubobject<UGenericTeamAgent>(TEXT("Team Agent"));
	_squadSharedData = CreateDefaultSubobject<USquadSharedData>(TEXT("Squad Shared Data"));
}

void ATheLeaderPlayerController::ChangePlayMode(EPlayerMode currPlayState)
{
	switch (currPlayState)
	{
	case EPlayerMode::FPSMODE:
	{
		USceneComponent* rootComponent = _commandModePawn->GetRootComponent();
		if (rootComponent != nullptr)
		{
			if (!_leaderPawn.IsValid())
			{
				_leaderPawn = _commandModePawn->GetLeader();
			}

			if (_leaderPawn.IsValid())
			{
				FVector location = _leaderPawn->GetActorLocation();
				location.Z += 300;
				rootComponent->SetWorldLocation(location);

				FRotator rotation = _leaderPawn->GetActorRotation();
				_commandModePawn->SetDirection(rotation.Yaw);

				SetMouseEnable(true);
			}

			Possess(_commandModePawn);
		}
		break;
	}
	case EPlayerMode::COMMODE:
	{
		SetMouseEnable(false);
		if (!_leaderPawn.IsValid())
		{
			_leaderPawn = _commandModePawn->GetLeader();
		}
		Possess(_leaderPawn.Get());
	}
		break;
	default:
		break;
	}
}

void ATheLeaderPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (_playerSensingPawn == nullptr)
	{
		_playerSensingPawn = GetWorld()->SpawnActor<APlayerSensorPawn>();

		APlayerSensingAIController* sensingAIController = Cast<APlayerSensingAIController>(_playerSensingPawn->GetController());
		sensingAIController->FindEnemy.BindUFunction(this, TEXT("SpottingEnemy"));
		sensingAIController->DisapearEnemy.BindUFunction(this, TEXT("DisapearEnemy"));
	}

	if (Cast<AFPSPawn>(InPawn) != nullptr)
	{
		_playerSensingPawn->AttachToActor(InPawn, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true));
	}
}

EBotFireAttitude ATheLeaderPlayerController::GetFireAttitude()
{
	return _fireAttitude->GetFireAttitude();
}

void ATheLeaderPlayerController::SetFireAttitude(EBotFireAttitude fireAttitude)
{
	_fireAttitude->SetFireAttitude(fireAttitude);
}

void ATheLeaderPlayerController::SetGenericTeamId(FGenericTeamId TeamID)
{
	_teamAgent->SetGenericTeamId(TeamID);
}

FGenericTeamId ATheLeaderPlayerController::GetGenericTeamId() const
{
	return _teamAgent->GetGenericTeamId();
}

ETeamAttitude::Type ATheLeaderPlayerController::GetTeamAttitudeTowards(const AActor& Other) const
{
	return _teamAgent->GetTeamAttitudeTowards(Other);
}

void ATheLeaderPlayerController::SetSquadSharedData(SquadSharedData* squadSharedData)
{
	_squadSharedData->SetSquadSharedData(squadSharedData);
}

void ATheLeaderPlayerController::SpottingEnemy(AFPSPawn* targetPawn)
{
	UE_LOG(LogTemp, Log, TEXT("Spotting"));
	_squadSharedData->Spotting(targetPawn);
}

void ATheLeaderPlayerController::DisapearEnemy(AFPSPawn* targetPawn)
{
	UE_LOG(LogTemp, Log, TEXT("Disapear"));
	_squadSharedData->Disapear(targetPawn);
}

bool ATheLeaderPlayerController::HasSpotted(AFPSPawn* target)
{
	return _squadSharedData->HasSpotted(target);
}
