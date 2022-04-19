// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "TheLeaderCommonData.h"
#include "FireAttitudeDelegateInterface.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSAIController.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API AFPSAIController : public AAIController, public IFireAttitudeDelegateInterface
{
	GENERATED_BODY()
	
public:
	AFPSAIController();

	virtual void OnPossess(APawn* InPawn) override;

	EBotState getState();
	void setState(EBotState setupState);

	void setAttitude(EBotFireAttitude attitude);

	static const FName Destination;
	static const FName State;

private:
	UPROPERTY()
	UBehaviorTree* BTAsset;

	UPROPERTY()
	UBlackboardData* BBAsset;

	EBotState _currentState;
	EBotFireAttitude _currentAttitude;
};
