// Fill out your copyright notice in the Description page of Project Settings.


#include "TheLeaderPlayerController.h"
#include "CommanderPawn.h"

ATheLeaderPlayerController::TheLeaderPlayerControllerBuilder ATheLeaderPlayerController::_builder;

ATheLeaderPlayerController::ATheLeaderPlayerController()
{
	_attitude = NewObject<UFireAttitude>();
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

void ATheLeaderPlayerController::SetFireAttitude(EBotFireAttitude attitude)
{
	_attitude->SetFireAttitude(attitude);
}

EBotFireAttitude ATheLeaderPlayerController::GetFireAttitude()
{
	return _attitude->GetFireAttitude();
}

ATheLeaderPlayerController::TheLeaderPlayerControllerBuilder& ATheLeaderPlayerController::Builder()
{
	_builder.clear();
	return _builder;
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

ATheLeaderPlayerController::TheLeaderPlayerControllerBuilder::TheLeaderPlayerControllerBuilder()
{
	clear();
}

void ATheLeaderPlayerController::TheLeaderPlayerControllerBuilder::Build(UObject* param)
{
	ATheLeaderPlayerController* controller = Cast<ATheLeaderPlayerController>(param);

	controller->_attitude->SetFireAttitude(_attitude);

	clear();
}

void ATheLeaderPlayerController::TheLeaderPlayerControllerBuilder::clear()
{
	_attitude = EBotFireAttitude::FIREATWILL;
}

ATheLeaderPlayerController::TheLeaderPlayerControllerBuilder& ATheLeaderPlayerController::TheLeaderPlayerControllerBuilder::FireAttitude(EBotFireAttitude attitude)
{
	_attitude = attitude;
	return *this;
}
