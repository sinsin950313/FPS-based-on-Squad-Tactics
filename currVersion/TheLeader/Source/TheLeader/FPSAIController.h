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
#include "Interface/AISensorInterface.h"
#include "AISensingUpdater.h"
#include "PositionPointer.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSAIController.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API AFPSAIController : public AAIController, public IInGameControllerInterface, public IAISensorInterface
{
	GENERATED_BODY()
	
public:
	AFPSAIController();
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	static const FName kDestination;
	static const FName kState;
	static const FName kFireAttitude;
	static const FName kLookAt;
	static const FName kTarget;
private:
	UPROPERTY()
	UBehaviorTree* _BTAsset;
	UPROPERTY()
	UBlackboardData* _BBAsset;

//private:
//	EBotState _currentState;
//public:
//	EBotState GetState();
//	void SetState(EBotState state);
private:
	int32 _stateFlag;
public:
	void SetStateFlag(EBotStateFlag flag);
	void OffStateFlag(EBotStateFlag flag);
	int32 GetStateFlag();

public:
	//void MoveToDestination(FVector destination);
	void LookAt(FVector that);

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
	
//private:
//	UPROPERTY()
//	USquadSharedData* _squadSharedData;
public:
	virtual void SetSquadSharedData(SquadSharedData* squadSharedData) override;
	void SpottingEnemy(AFPSPawn* pawn);
	void DisappearEnemy(AFPSPawn* pawn);
	bool IsSpotted(AFPSPawn* target);
	bool HasSpotted();
private:
	bool _isSpotting;
	//EBotState _beforeState;
public:
	void Spotting();
	void NotSpotting();
	AFPSPawn* GetSpottedEnemy();

private:
	//virtual void SetDefaultSensor() override;
	virtual void SetSightConfig(AFPSPawn* pawn) override;

private:
	UPROPERTY()
	UAISensingUpdater* _sensingUpdater;
//public:
	virtual UAISensingUpdater* GetSensingUpdater() override;

public:
	virtual void SensingUpdate(AActor* Actor, FAIStimulus Stimulus) override;

private:
	TWeakObjectPtr<APositionPointer> _position;
public:
	void SetPosition(APositionPointer* position);
	FVector GetDestination();
};
