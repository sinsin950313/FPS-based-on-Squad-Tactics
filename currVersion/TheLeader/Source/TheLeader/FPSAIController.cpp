// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FPSPawn.h"

const FName AFPSAIController::kDestination(TEXT("Destination"));
const FName AFPSAIController::kState(TEXT("State"));
const FName AFPSAIController::kLookAt(TEXT("LookAt"));
const FName AFPSAIController::kFind(TEXT("Find"));

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

	Init();

	SetSenseConfig();

	ControllerBuilder::GetInstance()
		->InitTeam(ETeam::ENEMY)
		->SharedDataSet(nullptr)
		->Build(this);
}

void AFPSAIController::SetSenseConfig()
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent")));

	_senseConfigSight = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	_senseConfigSight->SightRadius = 300;
	_senseConfigSight->LoseSightRadius = 600;
	_senseConfigSight->PeripheralVisionAngleDegrees = 90;
	_senseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	_senseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	_senseConfigSight->DetectionByAffiliation.bDetectNeutrals = false;
	_senseConfigSight->SetMaxAge(10);
	GetPerceptionComponent()->ConfigureSense(*_senseConfigSight);

	GetPerceptionComponent()->SetDominantSense(*_senseConfigSight->GetSenseImplementation());

	SetGenericTeamId(FGenericTeamId(1));

	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AFPSAIController::Findable);
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
	Blackboard->SetValueAsVector(kDestination, destination);
}

void AFPSAIController::LookAt(FVector that)
{
	SetState(EBotState::MOVE);
	Blackboard->SetValueAsVector(kLookAt, that);
}

void AFPSAIController::SetFireAttitude(EBotFireAttitude fireAttitude)
{
	_fireAttitude->SetFireAttitude(fireAttitude);
}

EBotFireAttitude AFPSAIController::GetFireAttitude()
{
	return _fireAttitude->GetFireAttitude();
}

void AFPSAIController::Init()
{
	_fireAttitude = CreateDefaultSubobject<UFireAttitude>(TEXT("Fire Attitude"));
	_teamAgent = CreateDefaultSubobject<UGenericTeamAgent>(TEXT("Team Agent"));
	_squadSharedData = CreateDefaultSubobject<USquadSharedData>(TEXT("Squad Shared Data"));
}

void AFPSAIController::SetGenericTeamId(FGenericTeamId team)
{
	_teamAgent->SetGenericTeamId(team);
}

FGenericTeamId AFPSAIController::GetGenericTeamId() const
{
	return _teamAgent->GetGenericTeamId();
}

ETeamAttitude::Type AFPSAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	return _teamAgent->GetTeamAttitudeTowards(Other);
}

void AFPSAIController::SetSquadSharedData(SquadSharedData* squadSharedData)
{
	_squadSharedData->SetSquadSharedData(squadSharedData);
}

void AFPSAIController::SpottingEnemy(AFPSPawn* pawn)
{
	_squadSharedData->Spotting(pawn);
}

void AFPSAIController::DisapearEnemy(AFPSPawn* pawn)
{
	_squadSharedData->Disapear(pawn);
}

bool AFPSAIController::HasSpotted(AFPSPawn* pawn)
{
	return _squadSharedData->HasSpotted(pawn);
}

void AFPSAIController::Findable(AActor* Actor, FAIStimulus Stimulus)
{
	if (Cast<AFPSPawn>(Actor) != nullptr)
	{
		AFPSPawn* target = Cast<AFPSPawn>(Actor);
		if (Stimulus.WasSuccessfullySensed())
		{
			_squadSharedData->Spotting(target);
		}
		else
		{
			_squadSharedData->Disapear(target);
		}
	}
}
