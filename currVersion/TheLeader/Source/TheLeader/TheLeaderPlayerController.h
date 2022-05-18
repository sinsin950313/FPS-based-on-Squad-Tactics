// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheLeaderCommonData.h"
#include "CommanderPawn.h"
#include "FPSPawn.h"
#include "GenericTeamAgent.h"
#include "FireAttitude.h"
#include "PlayerSensingAIController.h"
#include "PlayerSensorPawn.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheLeaderPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API ATheLeaderPlayerController : public APlayerController, public IInGameControllerInterface
{
	GENERATED_BODY()
	
public:
	ATheLeaderPlayerController();

public:
	void ChangePlayMode(EPlayerMode currPlayState);
protected:
	virtual void OnPossess(APawn* InPawn) override;

protected:
	void BeginPlay() override;

private:
	UPROPERTY()
	ACommanderPawn* _commandModePawn;
	TWeakObjectPtr<AFPSPawn> _leaderPawn;

private:
	void SetMouseEnable(bool enable);

private:
	virtual void Init() override;

private:
	UPROPERTY()
	UFireAttitude* _fireAttitude;
public:
	EBotFireAttitude GetFireAttitude();
	virtual void SetFireAttitude(EBotFireAttitude fireAttitude) override;

private:
	UPROPERTY()
	UGenericTeamAgent* _teamAgent;
public:
	virtual void SetGenericTeamId(FGenericTeamId team) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	UFUNCTION()
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor* Other) const;
	
private:
	UPROPERTY()
	USquadSharedData* _squadSharedData;
public:
	virtual void SetSquadSharedData(SquadSharedData* squadSharedData) override;
	UFUNCTION()
	void SpottingEnemy(AFPSPawn* targetPawn);
	UFUNCTION()
	void DisapearEnemy(AFPSPawn* targetPawn);
	bool HasSpotted(AFPSPawn* target);

private:
	UPROPERTY()
	APlayerSensorPawn* _playerSensingPawn;
};
