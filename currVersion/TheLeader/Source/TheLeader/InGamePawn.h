// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InGamePawn.generated.h"

enum class EPlayerMode { FPSMODE, COMMODE };

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInGamePawn : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THELEADER_API IInGamePawn
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	EPlayerMode GetPlayMode() const;
	void SetPlayMode(EPlayerMode mode);
private:
	EPlayerMode _currentMode;
};
