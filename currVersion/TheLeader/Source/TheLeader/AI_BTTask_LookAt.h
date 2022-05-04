// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AI_BTTask_LookAt.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API UAI_BTTask_LookAt : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UAI_BTTask_LookAt();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
