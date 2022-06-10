// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_SetDestination.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "..\FPSAIController.h"

UBT_Service_SetDestination::UBT_Service_SetDestination()
{
	NodeName = TEXT("Set Destination");
}

void UBT_Service_SetDestination::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AFPSAIController* controller = Cast<AFPSAIController>(OwnerComp.GetAIOwner());
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AFPSAIController::kDestination, controller->GetDestination());
}
