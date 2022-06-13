// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_FPSPawnStateCheck.h"
#include "../FPSPawn.h"
#include "../FPSAIController.h"
#include "../TheLeaderCommonData.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_Service_FPSPawnStateCheck::UBT_Service_FPSPawnStateCheck()
{
	NodeName = TEXT("Pawn State Check");
	Interval = 1.0f;
}

void UBT_Service_FPSPawnStateCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AFPSAIController* controller = Cast<AFPSAIController>(OwnerComp.GetAIOwner());
	if (controller == nullptr)
	{
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AFPSAIController::kFireAttitude, controller->GetFireAttitude());

	int32 currentState = controller->GetStateFlag();

	UE_LOG(LogTemp, Log, TEXT("FPSPawnStateCheck need to get optimize state"));
	if (currentState & (1 << GetStateFlagShift(EBotStateFlag::ENGAGE)))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AFPSAIController::kState, EBotState::FIRE);
	}
	else if (currentState & (1 << GetStateFlagShift(EBotStateFlag::MOVE)))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AFPSAIController::kState, EBotState::MOVE);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AFPSAIController::kState, EBotState::WAIT);
	}
}
