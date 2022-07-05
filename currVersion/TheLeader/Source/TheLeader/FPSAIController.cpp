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

	_isSpotting = false;
}

void AFPSAIController::BeginPlay()
{
	Super::BeginPlay();

	_sensingUpdater->Run(GetPawn());
}

void AFPSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AISensorManager::GetInstance()->SetSightConfig(GetPerceptionComponent());

	if (UseBlackboard(_BBAsset, Blackboard))
	{
		FVector location;
		if (_position.IsValid())
		{
			location = _position.Get()->GetActorLocation();
		}
		else
		{
			location = InPawn->GetActorLocation();
		}

		Blackboard->SetValueAsVector(kDestination, location);
		if (!RunBehaviorTree(_BTAsset))
		{
			UE_LOG(LogTemp, Log, TEXT("AIController could't run BehaviorTree"));
		}
	}
}
//
//EBotState AFPSAIController::GetState()
//{
//	return _currentState;
//}
//
//void AFPSAIController::SetState(EBotState state)
//{
//	_currentState = state;
//}

//void AFPSAIController::MoveToDestination(FVector destination)
//{
//	Blackboard->SetValueAsVector(kDestination, destination);
//}

void AFPSAIController::SetStateFlag(EBotStateFlag flag)
{
	_stateFlag |= (1 << GetStateFlagShift(flag));
}

void AFPSAIController::OffStateFlag(EBotStateFlag flag)
{
	int32 offFlag = 0xFFFFFFFF;
	offFlag -= (1 << GetStateFlagShift(flag));
	_stateFlag &= offFlag;
}

int32 AFPSAIController::GetStateFlag()
{
	return _stateFlag;
}

void AFPSAIController::LookAt(FVector that)
{
	SetStateFlag(EBotStateFlag::MOVE);
	Blackboard->SetValueAsVector(kLookAt, that);
}

void AFPSAIController::SetFireAttitude(EBotFireAttitude fireAttitude)
{
	//UE_LOG(LogTemp, Log, TEXT("AI Change Attitude"));
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

void AFPSAIController::Spotting()
{
	if (!_isSpotting)
	{
		SetStateFlag(EBotStateFlag::ENGAGE);
		_isSpotting = true;
	}
}

void AFPSAIController::NotSpotting()
{
	if (_isSpotting)
	{
		OffStateFlag(EBotStateFlag::ENGAGE);
		_isSpotting = false;
	}
}

AFPSPawn* AFPSAIController::GetSpottedEnemy()
{
	//TMap<TWeakObjectPtr<AFPSPawn>, int32>* spottedEnemies = _squadSharedData->GetSpottedEnemies();
	TMap<TWeakObjectPtr<AFPSPawn>, int32>* spottedEnemies = GetSensingUpdater()->GetSpottedEnemies();

	UE_LOG(LogTemp, Warning, TEXT("FPSAIController GetSpottedEnemy need to get optimize Enemy"));

	if (spottedEnemies->Num() != 0)
	{
		auto iter = spottedEnemies->CreateIterator();
		return iter.Key().Get();
	}
	return nullptr;
}

//void AFPSAIController::SetDefaultSensor()
//{
//	AISensorManager::GetInstance()->SetDefaultSense(this);
//}

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

void AFPSAIController::SetPosition(APositionPointer* position)
{
	_position = position;
}

FVector AFPSAIController::GetDestination()
{
	return _position.IsValid() ? _position.Get()->GetActorLocation() : GetPawn()->GetActorLocation();
}
