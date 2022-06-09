// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PositionPointerAIController.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API APositionPointerAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	APositionPointerAIController();
private:
	UPROPERTY()
	UBlackboardData* _BBAsset;
	UPROPERTY()
	UBehaviorTree* _BTAsset;

public:
	virtual void OnPossess(APawn* InPawn) override;

private:
	static const FName kDestination;
public:
	void SetDestination(FVector destination);
};
