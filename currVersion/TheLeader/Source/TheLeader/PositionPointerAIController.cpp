// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionPointerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

const FName APositionPointerAIController::kDestination(TEXT("Destination"));

APositionPointerAIController::APositionPointerAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/PositionPointerBlackBoard.PositionPointerBlackBoard'"));
	if (BBObject.Succeeded())
	{
		_BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/PositionPointerBehaviorTree.PositionPointerBehaviorTree'"));
	if (BTObject.Succeeded())
	{
		_BTAsset = BTObject.Object;
	}
}

void APositionPointerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(_BBAsset, Blackboard))
	{
		if (!RunBehaviorTree(_BTAsset))
		{
			UE_LOG(LogTemp, Log, TEXT("PositionPointerAIController could't run BehaviorTree"));
		}
	}
}

void APositionPointerAIController::SetDestination(FVector destination)
{
	Blackboard->SetValueAsVector(kDestination, destination);
}
