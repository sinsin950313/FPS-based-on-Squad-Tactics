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
	bool HasSpotted(AFPSPawn* target);
};

UCLASS()
class THELEADER_API USquadSharedData : public UObject
{
	GENERATED_BODY()
	
private:
	SquadSharedData* _pSquadSharedData;
	TArray<TWeakObjectPtr<AFPSPawn>> _spotted;
public:
	void SetSquadSharedData(SquadSharedData* squadSharedData);
	void Spotting(AFPSPawn* pawn);
	void Disapear(AFPSPawn* pawn);
	bool HasSpotted(AFPSPawn* target);
};
