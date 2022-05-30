// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Perception/AISenseConfig_Sight.h" 
#include "FPSPawn.h"
#include "SquadSharedData.h"
#include "Interface/AISensorInterface.h"
#include "AISensorManager.h"
#include "GenericTeamAgent.h"
#include "AISensingUpdater.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerSensingAIController.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API APlayerSensingAIController : public AAIController, public IAISensorInterface
{
	GENERATED_BODY()

public:
	APlayerSensingAIController();

public:
	void SetDefaultSensor() override;
	void SetSightConfig(AFPSPawn* pawn) override;

private:
	USquadSharedData* _squadSharedData;
public:
	void SetSquadSharedData(SquadSharedData* squadSharedData);
	UFUNCTION()
	void SpottingEnemy(AFPSPawn* targetPawn);
	UFUNCTION()
	void DisappearEnemy(AFPSPawn* targetPawn);
	bool IsSpotted(AFPSPawn* target);
	bool HasSpotted();

private:
	UPROPERTY()
	UGenericTeamAgent* _teamAgent;
public:
	void SetTeam(UGenericTeamAgent* team);
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

private:
	UAISensingUpdater* _sensingUpdater;
public:
	virtual UAISensingUpdater* GetSensingUpdater() override;

public:
	virtual void SensingUpdate(AActor* Actor, FAIStimulus Stimulus) override;
};
