// Fill out your copyright notice in the Description page of Project Settings.


#include "SquadSharedData.h"

void SquadSharedData::Spotted(AFPSPawn* pawn)
{
	if (!_spotted.Contains(pawn))
	{
		_spotted.Add(pawn, 0);
		pawn->SetActorHiddenInGame(false);
	}
	int* ptr = _spotted.Find(pawn);
	++(*ptr);
}

void SquadSharedData::Disapear(AFPSPawn* pawn)
{
	int* ptr = _spotted.Find(pawn);
	--(*ptr);
	if (*ptr == 0)
	{
		pawn->SetActorHiddenInGame(true);
		_spotted.Remove(pawn);
	}
}

bool SquadSharedData::IsSpotted(AFPSPawn* target)
{
	return _spotted.Contains(target);
}

bool SquadSharedData::HasSpotted()
{
	return _spotted.Num() != 0;
}

TMap<TWeakObjectPtr<AFPSPawn>, int32>* SquadSharedData::GetSpottedEnemies()
{
	return &_spotted;
}

USquadSharedData::USquadSharedData()
{
	_pSquadSharedData = new SquadSharedData();
	_isSquadSharedData = false;
}

USquadSharedData::~USquadSharedData()
{
	if (!_isSquadSharedData)
	{
		delete _pSquadSharedData;
	}
}

void USquadSharedData::SetSquadSharedData(SquadSharedData* squadSharedData)
{
	if (squadSharedData != nullptr)
	{
		if (!_isSquadSharedData)
		{
			delete _pSquadSharedData;
		}
		_pSquadSharedData = squadSharedData;
		_isSquadSharedData = true;
	}
}

void USquadSharedData::Spotting(AFPSPawn* pawn)
{
	_pSquadSharedData->Spotted(pawn);
}

void USquadSharedData::Disapear(AFPSPawn* pawn)
{
	_pSquadSharedData->Disapear(pawn);
}

bool USquadSharedData::IsSpotted(AFPSPawn* target)
{
	return _pSquadSharedData->IsSpotted(target);
}

bool USquadSharedData::HasSpotted()
{
	return _pSquadSharedData->HasSpotted();
}

TMap<TWeakObjectPtr<AFPSPawn>, int32>* USquadSharedData::GetSpottedEnemies()
{
	return _pSquadSharedData->GetSpottedEnemies();
}
