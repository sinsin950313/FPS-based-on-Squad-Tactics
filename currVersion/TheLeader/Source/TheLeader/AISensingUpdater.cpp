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

void UAISensingUpdater::Run(APawn* myPawn)
{
	_myPawn = myPawn;
	GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &UAISensingUpdater::Update, 1.0f, true);
}

void UAISensingUpdater::Update()
{
		UE_LOG(LogTemp, Log, TEXT("Update call"));
	//for (auto iter = _spotableList.CreateIterator(); ; ++iter)
	//{
	//}
}
