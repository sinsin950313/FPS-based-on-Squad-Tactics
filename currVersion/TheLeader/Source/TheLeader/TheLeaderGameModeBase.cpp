// Copyright Epic Games, Inc. All Rights Reserved.


#include "TheLeaderGameModeBase.h"
#include "FPSPawn.h"
#include "TheLeaderPlayerController.h"

ATheLeaderGameModeBase::ATheLeaderGameModeBase()
{
	DefaultPawnClass = AFPSPawn::StaticClass();
	PlayerControllerClass = ATheLeaderPlayerController::StaticClass();
}
