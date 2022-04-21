// Fill out your copyright notice in the Description page of Project Settings.


#include "TheLeaderPlayerController.h"
#include "CommanderPawn.h"

ATheLeaderPlayerController::ATheLeaderPlayerController()
{
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
