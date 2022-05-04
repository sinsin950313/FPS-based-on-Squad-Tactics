// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AFPSAIController::kDestination(TEXT("Destination"));
const FName AFPSAIController::kState(TEXT("State"));
const FName AFPSAIController::kLookAt(TEXT("LookAt"));

AFPSAIController::FPSAIControllerBuilder AFPSAIController::_builder;

AFPSAIController::AFPSAIController()
{
	_attitude = NewObject<UFireAttitude>();

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

void AFPSAIController::SetFireAttitude(EBotFireAttitude attitude)
{
	_attitude->SetFireAttitude(attitude);
}

EBotFireAttitude AFPSAIController::GetFireAttitude()
{
	return _attitude->GetFireAttitude();
}

AFPSAIController::FPSAIControllerBuilder& AFPSAIController::Builder()
{
	_builder.clear();
	return _builder;
}

void AFPSAIController::MoveToDestination(FVector destination)
{
	Blackboard->SetValueAsVector(kDestination, destination);
}

void AFPSAIController::LookAt(FVector that)
{
	SetState(EBotState::MOVE);
	Blackboard->SetValueAsVector(kLookAt, that);
}

AFPSAIController::FPSAIControllerBuilder::FPSAIControllerBuilder()
{
	clear();
}

void AFPSAIController::FPSAIControllerBuilder::Build(UObject* param)
{
	AFPSAIController* controller = Cast<AFPSAIController>(param);

	controller->_attitude->SetFireAttitude(_attitude);

	clear();
}

void AFPSAIController::FPSAIControllerBuilder::clear()
{
	_attitude = EBotFireAttitude::FIREATWILL;
}

AFPSAIController::FPSAIControllerBuilder& AFPSAIController::FPSAIControllerBuilder::FireAttitude(EBotFireAttitude attitude)
{
	_attitude = attitude;
	return *this;
}
