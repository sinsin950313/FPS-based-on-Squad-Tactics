// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BT_Task_MoveTo.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API UBT_Task_MoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	UBT_Task_MoveTo();
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* NodeMemory) override;
};
