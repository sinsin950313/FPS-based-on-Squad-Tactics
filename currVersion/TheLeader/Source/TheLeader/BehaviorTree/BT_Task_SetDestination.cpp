// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_SetDestination.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "FPSAIController.h"

UBT_Task_SetDestination::UBT_Task_SetDestination()
{
	NodeName = TEXT("Set Destination");
}

EBTNodeResult::Type UBT_Task_SetDestination::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (result == EBTNodeResult::Succeeded)
	{
		AFPSAIController* controller = Cast<AFPSAIController>(OwnerComp.GetAIOwner());
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AFPSAIController::kDestination, controller->GetDestination());
	}

	return result;
}
