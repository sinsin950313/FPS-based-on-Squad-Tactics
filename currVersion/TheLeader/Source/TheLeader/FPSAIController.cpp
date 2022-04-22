// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AFPSAIController::kDestination(TEXT("Destination"));
const FName AFPSAIController::kState(TEXT("State"));

AFPSAIController::AFPSAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/FPSAIBlackBoard.FPSAIBlackBoard"));
	if (BBObject.Succeeded())
	{
		_BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/FPSAIBehaviorTree.FPSAIBehaviorTree"));
	if (BTObject.Succeeded())
	{
		_BTAsset = BTObject.Object;
	}
}

void AFPSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(_BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(kDestination, InPawn->GetActorLocation());
		if (!RunBehaviorTree(_BTAsset))
		{
			UE_LOG(LogTemp, Log, TEXT("AIController could't run BehaviorTree"));
		}
	}
}

EBotState AFPSAIController::GetState()
{
	return _currentState;
}

void AFPSAIController::SetState(EBotState state)
{
	_currentState = state;
}

void AFPSAIController::MoveToDestination(FVector destination)
{
	SetState(EBotState::MOVE);
	Blackboard->SetValueAsVector(kDestination, destination);
}
