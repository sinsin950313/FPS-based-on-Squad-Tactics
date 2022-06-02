// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FPSPawn.h"
#include "AISensorManager.h"

const FName AFPSAIController::kDestination(TEXT("Destination"));
const FName AFPSAIController::kState(TEXT("State"));
const FName AFPSAIController::kFireAttitude(TEXT("FireAttitude"));
const FName AFPSAIController::kLookAt(TEXT("LookAt"));
const FName AFPSAIController::kTarget(TEXT("Target"));

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

	SetGenericTeamId(FGenericTeamId(ETeam::ENEMY));

	ControllerBuilder::GetInstance()
		->InitTeam(ETeam::ENEMY)
		->SharedDataSet(nullptr)
		->Build(this);
}

void AFPSAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AISensorManager::GetInstance()->SetSightConfig(GetPerceptionComponent());

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
	UE_LOG(LogTemp, Log, TEXT("AI Change Attitude"));
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
	//_squadSharedData = CreateDefaultSubobject<USquadSharedData>(TEXT("Squad Shared Data"));
	_sensingUpdater = CreateDefaultSubobject<UAISensingUpdater>(TEXT("Sensing Updater"));
	AISensorManager::GetInstance()->SetDefaultSense(this);
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
	//_squadSharedData->SetSquadSharedData(squadSharedData);
	_sensingUpdater->SetSquadSharedData(squadSharedData);
}

void AFPSAIController::SpottingEnemy(AFPSPawn* pawn)
{
	UE_LOG(LogTemp, Log, TEXT("Spotting"));
	//_squadSharedData->Spotting(pawn);
	GetSensingUpdater()->SpottingEnemy(pawn);
}

void AFPSAIController::DisappearEnemy(AFPSPawn* pawn)
{
	//_squadSharedData->Disapear(pawn);
	GetSensingUpdater()->DisappearEnemy(pawn);
}

bool AFPSAIController::IsSpotted(AFPSPawn* pawn)
{
	//return _squadSharedData->IsSpotted(pawn);
	return GetSensingUpdater()->IsSpotted(pawn);
}

bool AFPSAIController::HasSpotted()
{
	//return _squadSharedData->HasSpotted();
	return GetSensingUpdater()->HasSpotted();
}

AFPSPawn* AFPSAIController::GetSpottedEnemy()
{
	//TMap<TWeakObjectPtr<AFPSPawn>, int32>* spottedEnemies = _squadSharedData->GetSpottedEnemies();
	TMap<TWeakObjectPtr<AFPSPawn>, int32>* spottedEnemies = GetSensingUpdater()->GetSpottedEnemies();

	UE_LOG(LogTemp, Warning, TEXT("FPSAIController GetSpottedEnemy need to get optimize Enemy"));

	auto iter = spottedEnemies->CreateIterator();
	return iter.Key().Get();
}

void AFPSAIController::SetDefaultSensor()
{
	AISensorManager::GetInstance()->SetDefaultSense(this);
}

void AFPSAIController::SetSightConfig(AFPSPawn* pawn)
{
	AISensorManager::GetInstance()->SetSightConfig(GetPerceptionComponent());
}

UAISensingUpdater* AFPSAIController::GetSensingUpdater()
{
	return _sensingUpdater;
}

void AFPSAIController::SensingUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	//AFPSPawn* pawn = Cast<AFPSPawn>(Actor);
	//if (pawn != nullptr)
	//{
	//	if (Stimulus.WasSuccessfullySensed())
	//	{
	//		SpottingEnemy(pawn);
	//	}
	//	else
	//	{
	//		DisappearEnemy(pawn);
	//	}
	//}
	GetSensingUpdater()->Sensing(Actor, Stimulus);
}
