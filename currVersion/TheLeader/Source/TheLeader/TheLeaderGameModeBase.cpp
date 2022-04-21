// Copyright Epic Games, Inc. All Rights Reserved.


#include "TheLeaderGameModeBase.h"
#include "CommanderPawn.h"
#include "TheLeaderPlayerController.h"

ATheLeaderGameModeBase::ATheLeaderGameModeBase()
{
	DefaultPawnClass = ACommanderPawn::StaticClass();
	PlayerControllerClass = ATheLeaderPlayerController::StaticClass();
}
