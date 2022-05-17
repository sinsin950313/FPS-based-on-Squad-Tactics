// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSensingAIController.h"
#include "Perception/AIPerceptionComponent.h"

APlayerSensingAIController::APlayerSensingAIController()
{
	SetSenseConfig();
}

void APlayerSensingAIController::SetSenseConfig()
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent")));

	_senseConfigSight = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	_senseConfigSight->SightRadius = 300;
	_senseConfigSight->LoseSightRadius = 600;
	_senseConfigSight->PeripheralVisionAngleDegrees = 90;
	_senseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	_senseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	_senseConfigSight->DetectionByAffiliation.bDetectNeutrals = false;
	_senseConfigSight->SetMaxAge(10);
	GetPerceptionComponent()->ConfigureSense(*_senseConfigSight);

	GetPerceptionComponent()->SetDominantSense(*_senseConfigSight->GetSenseImplementation());

	SetGenericTeamId(FGenericTeamId(2));

	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &APlayerSensingAIController::Findable);
}

void APlayerSensingAIController::Findable(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Log, TEXT("AAA"));
	if (Cast<AFPSPawn>(Actor) != nullptr)
	{
		AFPSPawn* target = Cast<AFPSPawn>(Actor);
		if (Stimulus.WasSuccessfullySensed())
		{
			FindEnemy.Execute(target);
		}
		else
		{
			DisapearEnemy.Execute(target);
		}
	}
}

ETeamAttitude::Type APlayerSensingAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	//brute force
	return ETeamAttitude::Hostile;
}
