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

UENUM(BlueprintType)
enum EBotFireAttitude
{
	FIREATWILL UMETA(DisplayName = "FIREATWILL"),
	HOLDFIRE UMETA(DisplayName = "HOLDFIRE")
};

enum class EBelonged
{
	PLAYER,
	ENEMY
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
