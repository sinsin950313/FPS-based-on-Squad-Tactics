// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPawnStateCheckBTService.h"
#include "FPSPawn.h"
#include "FPSAIController.h"
#include "TheLeaderCommonData.h"
#include "BehaviorTree/BlackboardComponent.h"

UFPSPawnStateCheckBTService::UFPSPawnStateCheckBTService()
{
	NodeName = TEXT("Pawn State Check");
	Interval = 1.0f;
}

void UFPSPawnStateCheckBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AFPSAIController* controller = Cast<AFPSAIController>(OwnerComp.GetAIOwner());
	if (controller == nullptr)
	{
		return;
	}

	AFPSPawn* controllingPawn = Cast<AFPSPawn>(controller->GetPawn());
	if (controllingPawn == nullptr)
	{
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AFPSAIController::State, controller->getState());
}
