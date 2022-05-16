// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GenericTeamAgentInterface.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GenericTeamAgent.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API UGenericTeamAgent : public UObject, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
private:
	FGenericTeamId _teamId;
public:
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
};
