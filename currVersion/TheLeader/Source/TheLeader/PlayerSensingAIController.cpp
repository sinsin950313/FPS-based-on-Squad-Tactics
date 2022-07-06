// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSensingAIController.h"
#include "Perception/AIPerceptionComponent.h"

APlayerSensingAIController::APlayerSensingAIController()
{
	SetGenericTeamId(FGenericTeamId(ETeam::PLAYER));

	//_squadSharedData = CreateDefaultSubobject<USquadSharedData>(TEXT("Squad Shared Data"));
	_sensingUpdater = CreateDefaultSubobject<UAISensingUpdater>(TEXT("Sensing Updater"));
	AISensorManager::GetInstance()->SetDefaultSense(this);

	//GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &APlayerSensingAIController::SensingUpdate);
}

//void APlayerSensingAIController::SetDefaultSensor()
//{
//	AISensorManager::GetInstance()->SetDefaultSense(this);
//}

void APlayerSensingAIController::SetSightConfig(AFPSPawn* pawn)
{
	AISensorManager::GetInstance()->SetSightConfig(GetPerceptionComponent());
}

void APlayerSensingAIController::SetSquadSharedData(SquadSharedData* squadSharedData)
{
	//_squadSharedData->SetSquadSharedData(squadSharedData);
	_sensingUpdater->SetSquadSharedData(squadSharedData);
}

void APlayerSensingAIController::SpottingEnemy(AFPSPawn* targetPawn)
{
	//_squadSharedData->Spotting(targetPawn);
	GetSensingUpdater()->SpottingEnemy(targetPawn);
}

void APlayerSensingAIController::DisappearEnemy(AFPSPawn* targetPawn)
{
	//_squadSharedData->Disapear(targetPawn);
	GetSensingUpdater()->DisappearEnemy(targetPawn);
}

bool APlayerSensingAIController::IsSpotted(AFPSPawn* target)
{
	//return _squadSharedData->IsSpotted(target);
	return GetSensingUpdater()->IsSpotted(target);
}

bool APlayerSensingAIController::HasSpotted()
{
	//return _squadSharedData->HasSpotted();
	return GetSensingUpdater()->HasSpotted();
}

void APlayerSensingAIController::SetTeam(UGenericTeamAgent* team)
{
	_teamAgent = team;
}

ETeamAttitude::Type APlayerSensingAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	return _teamAgent->GetTeamAttitudeTowards(Other);
}

UAISensingUpdater* APlayerSensingAIController::GetSensingUpdater()
{
	return _sensingUpdater;
}

void APlayerSensingAIController::SensingUpdate(AActor* Actor, FAIStimulus Stimulus)
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
	//GetSensingUpdater()->Sensing(Actor, Stimulus);
}

void APlayerSensingAIController::RunSensingUpdater(AFPSPawn* pawn)
{
	GetSensingUpdater()->Run(pawn);
}
