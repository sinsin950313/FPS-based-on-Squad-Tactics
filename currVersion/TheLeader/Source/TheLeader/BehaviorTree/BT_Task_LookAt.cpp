// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_LookAt.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "../FPSAIController.h"
#include "../FPSPawn.h"

UBT_Task_LookAt::UBT_Task_LookAt()
{
	NodeName = TEXT("LookAt");
}

EBTNodeResult::Type UBT_Task_LookAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AFPSPawn* controlPawn = Cast<AFPSPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (controlPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector from = controlPawn->GetActorLocation();
	FVector to = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AFPSAIController::kLookAt);
	FVector direction = to - from;
	FRotator rotator = direction.Rotation();
	rotator.Pitch = 0;
	controlPawn->SetActorRotation(rotator);

	return result;
}
