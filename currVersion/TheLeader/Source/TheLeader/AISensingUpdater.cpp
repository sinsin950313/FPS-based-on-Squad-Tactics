// Fill out your copyright notice in the Description page of Project Settings.


#include "AISensingUpdater.h"
#include "Perception\AIPerceptionTypes.h"
#include "SightSystemManager.h"

UAISensingUpdater::UAISensingUpdater()
{
	_squadSharedData = CreateDefaultSubobject<USquadSharedData>(TEXT("Squad Shared Data"));
}

UAISensingUpdater::~UAISensingUpdater()
{

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

TMap<TWeakObjectPtr<AFPSPawn>, int32>* UAISensingUpdater::GetSpottedEnemies()
{
	return _squadSharedData->GetSpottedEnemies();
}

bool UAISensingUpdater::IsSpotted(AFPSPawn* pawn)
{
	return _squadSharedData->IsSpotted(pawn);
}

bool UAISensingUpdater::HasSpotted()
{
	return _squadSharedData->HasSpotted();
}

void UAISensingUpdater::Sensing(AActor* Actor, FAIStimulus Stimulus)
{
	AFPSPawn* target = Cast<AFPSPawn>(Actor);
	if (target != nullptr)
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			//SpottingEnemy(pawn);
			spotable(target);
		}
		else
		{
			//DisappearEnemy(pawn);
			unspotable(target);
		}
	}
}

void UAISensingUpdater::Run(AFPSPawn* myPawn)
{
	_myPawn = myPawn;
	GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &UAISensingUpdater::Update, 1.0f, true);
}

void UAISensingUpdater::Update()
{
	for (auto iter = _spotableList.CreateIterator(); iter; ++iter)
	{
		AFPSPawn* target = _spotableList[iter.GetId()];
		if (SightSystemManager::GetInstance().IsSpotted(target, _myPawn))
		{
			SpottingEnemy(target);
		}
		else
		{
			DisappearEnemy(target);
		}
	}
}

void UAISensingUpdater::spotable(AFPSPawn* enemy)
{
	_spotableList.Add(enemy);
}

void UAISensingUpdater::unspotable(AFPSPawn* enemy)
{
	_spotableList.Remove(enemy);
}
