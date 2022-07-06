// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GenericTeamAgent.h"
#include "SquadSharedData.h"
#include "FPSPawn.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerSensorPawn.generated.h"

UCLASS()
class THELEADER_API APlayerSensorPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerSensorPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//void SetDefaultSensor();
	void SetSightConfig(AFPSPawn* pawn);

public:
	void SetSquadSharedData(SquadSharedData* squadSharedData);

public:
	void SetTeam(UGenericTeamAgent* teamAgent);

public:
	void RunSensingUpdater(AFPSPawn* pawn);
};
