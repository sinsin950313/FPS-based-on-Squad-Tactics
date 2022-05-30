// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FPSPawn.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SquadSharedData.generated.h"

/**
 * 
 */

class SquadSharedData
{
private:
	TMap<TWeakObjectPtr<AFPSPawn>, int32> _spotted;
public:
	void Spotted(AFPSPawn* pawn);
	void Disapear(AFPSPawn* pawn);
	bool IsSpotted(AFPSPawn* target);
	bool HasSpotted();
	TMap<TWeakObjectPtr<AFPSPawn>, int32>* GetSpottedEnemies();
};

UCLASS()
class THELEADER_API USquadSharedData : public UObject
{
	GENERATED_BODY()

public:
	USquadSharedData();
	~USquadSharedData();
	
private:
	bool _isSquadSharedData;
	SquadSharedData* _pSquadSharedData;
public:
	void SetSquadSharedData(SquadSharedData* squadSharedData);
	void Spotting(AFPSPawn* pawn);
	void Disapear(AFPSPawn* pawn);
	bool IsSpotted(AFPSPawn* target);
	bool HasSpotted();
	TMap<TWeakObjectPtr<AFPSPawn>, int32>* GetSpottedEnemies();
};
