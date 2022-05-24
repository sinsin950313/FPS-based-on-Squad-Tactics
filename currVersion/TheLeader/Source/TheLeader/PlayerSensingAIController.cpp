// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSensingAIController.h"
#include "Perception/AIPerceptionComponent.h"

APlayerSensingAIController::APlayerSensingAIController()
{
	SetGenericTeamId(FGenericTeamId(ETeam::PLAYER));

	_sensingUpdater = CreateDefaultSubobject<UAISensingUpdater>(TEXT("Sensing Updater"));
	AISensorManager::GetInstance()->SetDefaultSense(this);
}

void APlayerSensingAIController::SetDefaultSensor()
{
	AISensorManager::GetInstance()->SetDefaultSense(this);
}

void APlayerSensingAIController::SetSightConfig(AFPSPawn* pawn)
{
	AISensorManager::GetInstance()->SetSightConfig(GetPerceptionComponent());
}

void APlayerSensingAIController::SetSquadSharedData(SquadSharedData* squadSharedData)
{
	_squadSharedData->SetSquadSharedData(squadSharedData);
	_sensingUpdater->SetSquadSharedData(squadSharedData);
}

void APlayerSensingAIController::SpottingEnemy(AFPSPawn* targetPawn)
{
	_squadSharedData->Spotting(targetPawn);
}

void APlayerSensingAIController::DisapearEnemy(AFPSPawn* targetPawn)
{
	_squadSharedData->Disapear(targetPawn);
}

bool APlayerSensingAIController::HasSpotted(AFPSPawn* target)
{
	return _squadSharedData->HasSpotted(target);
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
