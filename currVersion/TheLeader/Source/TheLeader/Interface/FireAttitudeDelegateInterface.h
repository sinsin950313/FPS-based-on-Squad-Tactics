// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TheLeaderCommonData.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FireAttitudeDelegateInterface.generated.h"

DECLARE_DELEGATE_OneParam(FChangeFireAttitude, EBotFireAttitude);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFireAttitudeDelegateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THELEADER_API IFireAttitudeDelegateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FChangeFireAttitude FireAttitudeDelegate;
};
