// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "ControllerBuilder.h"
#include "Perception/AISenseConfig_Sight.h" 
#include "Perception/AIPerceptionComponent.h"
#include "FireAttitude.h"
#include "SquadSharedData.h"
#include "GenericTeamAgent.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSAIController.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API AFPSAIController : public AAIController, public IInGameControllerInterface
{
	GENERATED_BODY()
	
public:
	AFPSAIController();
	virtual void OnPossess(APawn* InPawn) override;

public:
	static const FName kDestination;
	static const FName kState;
	static const FName kLookAt;
	static const FName kFind;
private:
	UPROPERTY()
	UBehaviorTree* _BTAsset;
	UPROPERTY()
	UBlackboardData* _BBAsset;

private:
	EBotState _currentState;
public:
	EBotState GetState();
	void SetState(EBotState state);

public:
	void MoveToDestination(FVector destination);
	void LookAt(FVector that);

private:
	UAISenseConfig_Sight* _senseConfigSight;
	void SetSenseConfig();

private:
	virtual void Init() override;

private:
	UPROPERTY()
	UFireAttitude* _fireAttitude;
public:
	EBotFireAttitude GetFireAttitude();
	virtual void SetFireAttitude(EBotFireAttitude fireAttitude) override;

private:
	UPROPERTY()
	UGenericTeamAgent* _teamAgent;
public:
	virtual void SetGenericTeamId(FGenericTeamId team) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
private:
	UPROPERTY()
	USquadSharedData* _squadSharedData;
public:
	virtual void SetSquadSharedData(SquadSharedData* squadSharedData) override;
	void SpottingEnemy(AFPSPawn* pawn);
	void DisapearEnemy(AFPSPawn* pawn);
	bool HasSpotted(AFPSPawn* target);

public:
	UFUNCTION()
	void Findable(AActor* Actor, FAIStimulus Stimulus);
};
