// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FPSPawnStateCheckBTService.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API UFPSPawnStateCheckBTService : public UBTService
{
	GENERATED_BODY()

public:
	UFPSPawnStateCheckBTService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
