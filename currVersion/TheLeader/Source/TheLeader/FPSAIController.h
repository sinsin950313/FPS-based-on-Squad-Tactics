// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "TheLeaderCommonData.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSAIController.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API AFPSAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AFPSAIController();

	virtual void OnPossess(APawn* InPawn) override;

	EBotFireAttitude getAttitude();
	void setAttitude(EBotFireAttitude attitude);

	EBotState getState();
	void setState(EBotState setupState);

	static const FName destination;
	static const FName state;
	static const FName fireAttitude;

private:
	UPROPERTY()
	UBehaviorTree* BTAsset;

	UPROPERTY()
	UBlackboardData* BBAsset;

	EBotState _currentState;
	EBotFireAttitude _currentAttitude;
};
