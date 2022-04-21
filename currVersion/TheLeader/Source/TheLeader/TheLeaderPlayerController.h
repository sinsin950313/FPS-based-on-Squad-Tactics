// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheLeaderCommonData.h"
#include "FPSPawn.h"
#include "Fireable.h"
#include "CommanderPawn.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheLeaderPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API ATheLeaderPlayerController : public APlayerController, public IFireable
{
	GENERATED_BODY()
	
public:
	ATheLeaderPlayerController();
	void ChangePlayMode(EPlayerMode currPlayState);

protected:
	void BeginPlay() override;

private:
	UPROPERTY()
	ACommanderPawn* _commandModePawn;
	TWeakObjectPtr<AFPSPawn> _leaderPawn;

	void SetMouseEnable(bool enable);
};
