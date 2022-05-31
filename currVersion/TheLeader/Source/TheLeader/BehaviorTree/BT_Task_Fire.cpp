// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_Fire.h"
#include "../FPSAIController.h"
#include "../FPSPawn.h"
#include "BehaviorTree/BlackboardComponent.h" 

UBT_Task_Fire::UBT_Task_Fire()
{
	NodeName = TEXT("Fire");
}

EBTNodeResult::Type UBT_Task_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (result == EBTNodeResult::Succeeded)
	{
		AFPSPawn* pawn = Cast<AFPSPawn>(OwnerComp.GetAIOwner()->GetPawn());
		if (pawn != nullptr)
		{
			AFPSPawn* target = Cast<AFPSPawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AFPSAIController::kTarget));
			if (target != nullptr)
			{
				pawn->Fire();
			}
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}

	return result;
}