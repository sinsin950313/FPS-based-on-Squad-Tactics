// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_LookAt.h"
#include "../FPSAIController.h"
#include "BehaviorTree\BlackboardComponent.h"

UBT_Service_LookAt::UBT_Service_LookAt()
{
	NodeName = TEXT("Look At");
}

void UBT_Service_LookAt::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AFPSPawn* target = Cast<AFPSPawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AFPSAIController::kTarget));
	if (target == nullptr)
	{
		return;
	}

	AAIController* controller = OwnerComp.GetAIOwner();
	APawn* pawn = controller->GetPawn();
	FVector location = pawn->GetActorLocation();
	FVector targetLocation = target->GetActorLocation();
	FVector direction = targetLocation - location;

	pawn->SetActorRotation(direction.Rotation());
}
