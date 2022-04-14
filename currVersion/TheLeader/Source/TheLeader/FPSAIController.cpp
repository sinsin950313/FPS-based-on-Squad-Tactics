// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AFPSAIController::destination(TEXT("Destination"));
const FName AFPSAIController::state(TEXT("State"));

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
}

void AFPSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(destination, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Log, TEXT("AIController could't run BehaviorTree"));
		}
	}
}

EBotSetupState AFPSAIController::getSetupState()
{
	return _currentSetupState;
}

void AFPSAIController::setSetupState(EBotSetupState setupState)
{
	_currentSetupState = setupState;
}
