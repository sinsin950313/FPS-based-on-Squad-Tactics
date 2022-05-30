// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BT_Service_HasSpottedEnemy.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API UBT_Service_HasSpottedEnemy : public UBTService
{
	GENERATED_BODY()
	
public:
	UBT_Service_HasSpottedEnemy();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
