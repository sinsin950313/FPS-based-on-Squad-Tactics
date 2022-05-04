// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheLeaderCommonData.h"
#include "FPSPawn.h"
#include "CommanderPawn.h"
#include "TheLeaderCommonData.h"
#include "FireAttitude.h"
#include "CustomUObjectBuilder.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheLeaderPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API ATheLeaderPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATheLeaderPlayerController();

public:
	class TheLeaderPlayerControllerBuilder : public CustomUObjectBuilder
	{
	public:
		TheLeaderPlayerControllerBuilder();
		virtual void Build(UObject* param) override;
		virtual void clear() override;

	public:
		TheLeaderPlayerControllerBuilder& FireAttitude(EBotFireAttitude attitude);
	private:
		EBotFireAttitude _attitude;
	};
	TheLeaderPlayerControllerBuilder& Builder();
private:
	static TheLeaderPlayerControllerBuilder _builder;

public:
	void ChangePlayMode(EPlayerMode currPlayState);

protected:
	void BeginPlay() override;

private:
	UPROPERTY()
	ACommanderPawn* _commandModePawn;
	TWeakObjectPtr<AFPSPawn> _leaderPawn;

private:
	void SetMouseEnable(bool enable);

public:
	void SetFireAttitude(EBotFireAttitude attitude);
	EBotFireAttitude GetFireAttitude();
private:
	UPROPERTY()
	UFireAttitude* _attitude;
};
