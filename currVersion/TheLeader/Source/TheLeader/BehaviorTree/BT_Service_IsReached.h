// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BT_Service_IsReached.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API UBT_Service_IsReached : public UBTService
{
	GENERATED_BODY()

public:
	UBT_Service_IsReached();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float _reachedRadius;
	float Distance(FVector position1, FVector position2);
};
