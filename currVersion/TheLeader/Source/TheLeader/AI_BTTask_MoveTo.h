// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "AI_BTTask_MoveTo.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API UAI_BTTask_MoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* NodeMemory) override;
};
