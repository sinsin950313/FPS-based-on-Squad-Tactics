// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_LookTarget.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "../FPSPawn.h"
#include "../FPSAIController.h"

UBT_Task_LookTarget::UBT_Task_LookTarget()
{
	NodeName = TEXT("Look Target");
}

EBTNodeResult::Type UBT_Task_LookTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AFPSAIController* controller = Cast<AFPSAIController>(OwnerComp.GetAIOwner());
	if (controller == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AFPSPawn* target = Cast<AFPSPawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AFPSAIController::kTarget));
	if (target == nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AFPSAIController::kTarget, controller->GetSpottedEnemy());
		target = Cast<AFPSPawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AFPSAIController::kTarget));
	}

	if (target == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APawn* pawn = controller->GetPawn();
	FVector location = pawn->GetActorLocation();
	FVector targetLocation = target->GetActorLocation();
	FVector direction = targetLocation - location;

	pawn->SetActorRotation(direction.Rotation());

	return result;
}
