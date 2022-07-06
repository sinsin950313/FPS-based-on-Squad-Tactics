// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SquadSharedData.h"
#include "FPSPawn.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AISensingUpdater.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API UAISensingUpdater : public UObject
{
	GENERATED_BODY()

public:
	UAISensingUpdater();
	~UAISensingUpdater();

private:
	UPROPERTY()
	USquadSharedData* _squadSharedData;
public:
	void SetSquadSharedData(SquadSharedData* squadSharedData);
	void SpottingEnemy(AFPSPawn* pawn);
	void DisappearEnemy(AFPSPawn* pawn);
	TMap<TWeakObjectPtr<AFPSPawn>, int32>* GetSpottedEnemies();
	bool IsSpotted(AFPSPawn* pawn);
	bool HasSpotted();
	
public:
	UFUNCTION()
	void Sensing(AActor* Actor, FAIStimulus Stimulus);

private:
	FTimerHandle _timerHandle;
	AFPSPawn* _myPawn;
	TSet<AFPSPawn*> _spotableList;
public:
	void Run(AFPSPawn* myPawn);
private:
	UFUNCTION()
	void Update();

private:
	void spotable(AFPSPawn* enemy);
	void unspotable(AFPSPawn* enemy);
};
