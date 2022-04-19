// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AFPSAIController::Destination(TEXT("Destination"));
const FName AFPSAIController::State(TEXT("State"));

AFPSAIController::AFPSAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/FPSAIBlackBoard.FPSAIBlackBoard"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/FPSAIBehaviorTree.FPSAIBehaviorTree"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	Test();
}

void AFPSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(Destination, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Log, TEXT("AIController could't run BehaviorTree"));
		}
	}
}

EBotState AFPSAIController::getState()
{
	return _currentState;
}

void AFPSAIController::setState(EBotState setupState)
{
	_currentState = setupState;
}

void AFPSAIController::setAttitude(EBotFireAttitude attitude)
{
	UE_LOG(LogTemp, Log, TEXT("Set Attitude"));
	_currentAttitude = attitude;
}
