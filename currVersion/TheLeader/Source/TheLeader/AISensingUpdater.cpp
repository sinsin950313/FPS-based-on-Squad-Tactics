// Fill out your copyright notice in the Description page of Project Settings.


#include "AISensingUpdater.h"
#include "Perception\AIPerceptionTypes.h"
#include "FPSPawn.h"

UAISensingUpdater::UAISensingUpdater()
{
	_squadSharedData = CreateDefaultSubobject<USquadSharedData>(TEXT("Squad Shared Data"));
}

void UAISensingUpdater::SetSquadSharedData(SquadSharedData* squadSharedData)
{
	_squadSharedData->SetSquadSharedData(squadSharedData);
}

void UAISensingUpdater::SpottingEnemy(AFPSPawn* pawn)
{
	_squadSharedData->Spotting(pawn);
}

void UAISensingUpdater::DisappearEnemy(AFPSPawn* pawn)
{
	_squadSharedData->Disapear(pawn);
}

void UAISensingUpdater::Sensing(AActor* Actor, FAIStimulus Stimulus)
{
	AFPSPawn* pawn = Cast<AFPSPawn>(Actor);
	if (pawn != nullptr)
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			SpottingEnemy(pawn);
		}
		else
		{
			DisappearEnemy(pawn);
		}
	}
}
