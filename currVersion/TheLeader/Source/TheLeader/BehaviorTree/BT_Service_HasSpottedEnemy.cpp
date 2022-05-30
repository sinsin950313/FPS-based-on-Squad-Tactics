// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_HasSpottedEnemy.h"
#include "../FPSAIController.h"

UBT_Service_HasSpottedEnemy::UBT_Service_HasSpottedEnemy()
{
	NodeName = TEXT("Is Spotted Enemy Check");
}

void UBT_Service_HasSpottedEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AFPSAIController* controller = Cast<AFPSAIController>(OwnerComp.GetAIOwner());
	if (controller == nullptr)
	{
		return;
	}

	if (controller->HasSpotted())
	{
		controller->SetState(EBotState::FIRE);
	}
}
