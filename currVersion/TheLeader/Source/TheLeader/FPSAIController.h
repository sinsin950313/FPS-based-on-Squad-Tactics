// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "InGameController.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSAIController.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API AFPSAIController : public AAIController, public InGameController
{
	GENERATED_BODY()
	
public:
	AFPSAIController();
	virtual void OnPossess(APawn* InPawn) override;

public:
	EBotState GetState();
	void SetState(EBotState state);
private:
	EBotState _currentState;

public:
	static const FName kDestination;
	static const FName kState;
	static const FName kLookAt;
private:
	UPROPERTY()
	UBehaviorTree* _BTAsset;
	UPROPERTY()
	UBlackboardData* _BBAsset;

public:
	void MoveToDestination(FVector destination);
	void LookAt(FVector that);

public:
	UFUNCTION()
	void SetFireAttitude(EBotFireAttitude attitude) override;
};
