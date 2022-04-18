// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EPlayerMode { FPSMODE, COMMODE };

UENUM(BlueprintType)
enum EBotFireAttitude
{
	FIREATWILL UMETA(DisplayName = "FIREATWILL"),
	HOLDFIRE UMETA(DisplayName = "HOLDFIRE")
};

UENUM(BlueprintType)
enum EBotState
{
	WAIT UMETA(DisplayName = "WAIT"),
	MOVE UMETA(DisplayName = "MOVE"),
	FIRE UMETA(DisplayName = "FIRE")
};

class THELEADER_API TheLeaderCommonData
{
public:
	TheLeaderCommonData();
	~TheLeaderCommonData();
};
