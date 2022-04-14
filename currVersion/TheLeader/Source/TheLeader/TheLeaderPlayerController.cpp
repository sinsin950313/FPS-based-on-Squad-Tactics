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
void ATheLeaderPlayerController::changePlayMode(PlayState currPlayState)
{
	switch (currPlayState)
	{
	case PlayState::FPSMODE:
	{
		USceneComponent* rootComponent = _commandModePawn->GetRootComponent();
		if (rootComponent != nullptr)
		{
			FVector location = _fpsModePawn->GetActorLocation();
			location.Z += 300;
			rootComponent->SetWorldLocation(location);
			Possess(_commandModePawn);
		}
		break;
	}
	case PlayState::COMMODE:
		Possess(_fpsModePawn);
		break;
	default:
		break;
	}
}
