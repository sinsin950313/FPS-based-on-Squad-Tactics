// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_IsReached.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "..\FPSAIController.h"
#include "..\PositionPointer.h"

UBT_Service_IsReached::UBT_Service_IsReached()
{
	NodeName = TEXT("Is reached to Position");
	_reachedRadius = 50.0f;
}

void UBT_Service_IsReached::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AFPSAIController* controller = Cast<AFPSAIController>(OwnerComp.GetAIOwner());
	if (controller == nullptr)
	{
		return;
	}

	FVector current = controller->GetPawn()->GetActorLocation();
	FVector position = controller->GetDestination();
	if (_reachedRadius < Distance(current, position))
	{
		controller->SetStateFlag(EBotStateFlag::MOVE);
	}
	else
	{
		controller->OffStateFlag(EBotStateFlag::MOVE);
	}
}

float UBT_Service_IsReached::Distance(FVector position1, FVector position2)
{
	return FVector::Dist(position1, position2);
}
