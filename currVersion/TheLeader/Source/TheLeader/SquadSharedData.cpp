// Fill out your copyright notice in the Description page of Project Settings.


#include "SquadSharedData.h"

void SquadSharedData::Spotted(AFPSPawn* pawn)
{
	if (!_spotted.Contains(pawn))
	{
		_spotted.Add(pawn, 0);
	}
	int* ptr = _spotted.Find(pawn);
	*(++ptr);
}

void SquadSharedData::Disapear(AFPSPawn* pawn)
{
	int* ptr = _spotted.Find(pawn);
	*(--ptr);
	if (*ptr == 0)
	{
		_spotted.Remove(pawn);
	}
}

bool SquadSharedData::HasSpotted(AFPSPawn* target)
{
	return _spotted.Contains(target);
}

void USquadSharedData::SetSquadSharedData(SquadSharedData* squadSharedData)
{
	_pSquadSharedData = squadSharedData;
}

void USquadSharedData::Spotted(AFPSPawn* pawn)
{
	if (_pSquadSharedData != nullptr)
	{
		_pSquadSharedData->Spotted(pawn);
	}
	else
	{
		_spotted.Add(pawn);
	}
}

void USquadSharedData::Disapear(AFPSPawn* pawn)
{
	if (_pSquadSharedData != nullptr)
	{
		_pSquadSharedData->Disapear(pawn);
	}
	else
	{
		_spotted.Remove(pawn);
	}
}

bool USquadSharedData::HasSpotted(AFPSPawn* target)
{
	if (_pSquadSharedData != nullptr)
	{
		return _pSquadSharedData->HasSpotted(target);
	}
	else
	{
		return _spotted.Contains(target);
	}
}
