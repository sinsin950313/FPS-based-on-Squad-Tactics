// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Perception/AISenseConfig_Sight.h" 
#include "FPSPawn.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerSensingAIController.generated.h"

DECLARE_DELEGATE_OneParam(FRegisterDelegate, AFPSPawn*);

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
	FRegisterDelegate FindEnemy;
	FRegisterDelegate DisapearEnemy;
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
};
