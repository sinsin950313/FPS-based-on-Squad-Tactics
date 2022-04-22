// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_BTTask_MoveTo.h"
#include "FPSAIController.h"

EBTNodeResult::Type UAI_BTTask_MoveTo::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type res = Super::ExecuteTask(ownerComp, NodeMemory);
	if (res == EBTNodeResult::Succeeded)
	{
		AFPSAIController* controller = Cast<AFPSAIController>(ownerComp.GetAIOwner());
		controller->SetState(EBotState::WAIT);
	}
	return res;
}
