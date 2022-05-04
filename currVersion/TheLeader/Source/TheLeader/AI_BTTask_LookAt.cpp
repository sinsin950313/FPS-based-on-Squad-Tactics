// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_BTTask_LookAt.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "FPSAIController.h"
#include "FPSPawn.h"

UAI_BTTask_LookAt::UAI_BTTask_LookAt()
{
	NodeName = TEXT("LookAt");
}

EBTNodeResult::Type UAI_BTTask_LookAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	controlPawn->SetActorRotation(direction.Rotation());

	return result;
}
