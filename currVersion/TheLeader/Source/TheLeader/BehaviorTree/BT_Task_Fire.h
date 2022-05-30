// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_Task_Fire.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API UBT_Task_Fire : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBT_Task_Fire();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
