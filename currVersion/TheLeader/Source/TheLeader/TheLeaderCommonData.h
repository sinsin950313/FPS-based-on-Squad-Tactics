// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class PlayState { FPSMODE, COMMODE };
enum class BotFireState { FIREATWILL, HOLDFIRE };

UENUM(BlueprintType)
enum EBotSetupState
{
	WAIT UMETA(DisplayName = "WAIT"),
	MOVE UMETA(DisplayName = "MOVE"),
	FIRE UMETA(DisplayName = "FIRE"),
	NONE UMETA(DisplayName = "NONE")
};
/**
 * 
 */
class THELEADER_API TheLeaderCommonData
{
public:
	TheLeaderCommonData();
	~TheLeaderCommonData();
};
