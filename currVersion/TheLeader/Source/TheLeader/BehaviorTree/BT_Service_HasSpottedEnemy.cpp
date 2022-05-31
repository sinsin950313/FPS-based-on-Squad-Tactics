// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_HasSpottedEnemy.h"
#include "../FPSAIController.h"
#include "BehaviorTree\BlackboardComponent.h"

UBT_Service_HasSpottedEnemy::UBT_Service_HasSpottedEnemy()
{
	NodeName = TEXT("Is Spotted Enemy Check");
	_spottedBefore = false;
}

void UBT_Service_HasSpottedEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AFPSAIController* controller = Cast<AFPSAIController>(OwnerComp.GetAIOwner());
	if (controller == nullptr)
	{
		return;
	}

	AFPSPawn* pawn = Cast<AFPSPawn>(controller->GetPawn());
	if (pawn == nullptr)
	{
		return;
	}

	if (controller->HasSpotted())
	{
		AFPSPawn* enemy = controller->GetSpottedEnemy();
		if (enemy != nullptr)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(AFPSAIController::kTarget, enemy);
			_beforeState = static_cast<EBotState>(OwnerComp.GetBlackboardComponent()->GetValueAsEnum(AFPSAIController::kState));
			_spottedBefore = true;
			controller->SetState(EBotState::FIRE);
			pawn->AttackStart();
		}
	}
	else
	{
		if (_spottedBefore)
		{
			controller->SetState(_beforeState);
			pawn->AttackStop();
			_spottedBefore = false;
		}
	}
}
