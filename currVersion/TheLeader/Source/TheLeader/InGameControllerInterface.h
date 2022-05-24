// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GenericTeamAgentInterface.h"
#include "TheLeaderCommonData.h"
#include "SquadSharedData.h"
#include "Perception/AIPerceptionComponent.h" 

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InGameControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInGameControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THELEADER_API IInGameControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Init() = 0;

public:
	virtual void SetGenericTeamId(FGenericTeamId team) = 0;
	virtual FGenericTeamId GetGenericTeamId() const = 0;

public:
	UFUNCTION()
	virtual void SetFireAttitude(EBotFireAttitude fireAttitude) = 0;
	
public:
	virtual void SetSquadSharedData(SquadSharedData* squadSharedData) = 0;
};
