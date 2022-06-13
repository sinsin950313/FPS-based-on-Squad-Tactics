// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_MoveTo.h"
#include "../FPSAIController.h"

UBT_Task_MoveTo::UBT_Task_MoveTo()
{
	NodeName = TEXT("Move To");
}

EBTNodeResult::Type UBT_Task_MoveTo::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type res = Super::ExecuteTask(ownerComp, NodeMemory);
	if (res == EBTNodeResult::Succeeded)
	{
		AFPSAIController* controller = Cast<AFPSAIController>(ownerComp.GetAIOwner());
		controller->OffStateFlag(EBotStateFlag::MOVE);
	}
	return res;
}
