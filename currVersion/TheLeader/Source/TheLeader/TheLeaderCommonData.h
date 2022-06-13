// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EBotState
{
	WAIT UMETA(DisplayName = "WAIT"),
	MOVE UMETA(DisplayName = "MOVE"),
	FIRE UMETA(DisplayName = "FIRE")
};

enum class EBotStateFlag : int8
{
	MOVE,
	ENGAGE
};

int8 GetStateFlagShift(EBotStateFlag flag);

UENUM(BlueprintType)
enum EBotFireAttitude
{
	FIREATWILL UMETA(DisplayName = "FIREATWILL"),
	HOLDFIRE UMETA(DisplayName = "HOLDFIRE")
};

enum ETeam : uint8
{
	NEUTRAL,
	ENEMY,
	PLAYER
};

enum class EPlayerMode
{
	FPSMODE,
	COMMODE
};

class THELEADER_API TheLeaderCommonData
{
public:
	TheLeaderCommonData();
	~TheLeaderCommonData();
};
