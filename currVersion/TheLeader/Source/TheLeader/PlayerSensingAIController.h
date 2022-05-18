// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Perception/AISenseConfig_Sight.h" 
#include "FPSPawn.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerSensingAIController.generated.h"

DECLARE_DELEGATE_OneParam(FRegisterDelegate, AFPSPawn*);
DECLARE_DELEGATE_RetVal_OneParam(ETeamAttitude::Type, FAttitudeDelegate, const AActor*);

/**
 * 
 */
UCLASS()
class THELEADER_API APlayerSensingAIController : public AAIController
{
	GENERATED_BODY()

public:
	APlayerSensingAIController();
	
private:
	UAISenseConfig_Sight* _senseConfigSight;
	void SetSenseConfig();

public:
	UFUNCTION()
	void Findable(AActor* Actor, FAIStimulus Stimulus);
	FRegisterDelegate FindEnemyDelegate;
	FRegisterDelegate DisapearEnemyDelegate;

public:
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	FAttitudeDelegate TeamAttitudeDelegate;
};
