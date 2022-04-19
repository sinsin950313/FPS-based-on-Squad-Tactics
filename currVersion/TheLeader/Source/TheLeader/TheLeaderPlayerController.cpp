// Fill out your copyright notice in the Description page of Project Settings.


#include "TheLeaderPlayerController.h"
#include "CommanderPawn.h"

ATheLeaderPlayerController::ATheLeaderPlayerController()
{
}

void ATheLeaderPlayerController::BeginPlay()
{
	Super::BeginPlay();

	_fpsModePawn = GetPawn();
	_commandModePawn = Cast<ACommanderPawn>(GetWorld()->SpawnActor(ACommanderPawn::StaticClass()));
}
void ATheLeaderPlayerController::setMouseEnable(bool enable)
{
	bEnableMouseOverEvents = enable;
	bShowMouseCursor = enable;
}
void ATheLeaderPlayerController::changePlayMode(EPlayerMode currPlayState)
{
	switch (currPlayState)
	{
	case EPlayerMode::FPSMODE:
	{
		USceneComponent* rootComponent = _commandModePawn->GetRootComponent();
		if (rootComponent != nullptr)
		{
			FVector location = _fpsModePawn->GetActorLocation();
			location.Z += 300;
			rootComponent->SetWorldLocation(location);
			setMouseEnable(true);
			Possess(_commandModePawn);

			Cast<ACommanderPawn>(_commandModePawn)->changeFireAttitude(EBotFireAttitude::HOLDFIRE);
			UE_LOG(LogTemp, Log, TEXT("Temporarily set Hold Fire"));

		}
		break;
	}
	case EPlayerMode::COMMODE:
	{
		setMouseEnable(false);
		Possess(_fpsModePawn);
	}
		break;
	default:
		break;
	}
}
