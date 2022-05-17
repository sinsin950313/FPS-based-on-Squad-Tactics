// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericTeamAgent.h"
#include "FPSPawn.h"
#include "InGameControllerInterface.h"

void UGenericTeamAgent::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	_teamId = TeamID;
}

FGenericTeamId UGenericTeamAgent::GetGenericTeamId() const
{
	return _teamId;
}

ETeamAttitude::Type UGenericTeamAgent::GetTeamAttitudeTowards(const AActor& Other) const
{
	const AFPSPawn* pawn = Cast<const AFPSPawn>(&Other);
	if (pawn != nullptr)
	{
		const IInGameControllerInterface* teamInterface = Cast<const IInGameControllerInterface>(pawn->GetController());
		if (teamInterface != nullptr)
		{
			if (teamInterface->GetGenericTeamId() == ETeam::NEUTRAL)
				return ETeamAttitude::Neutral;

			return teamInterface->GetGenericTeamId() == GetGenericTeamId().GetId() ? ETeamAttitude::Friendly : ETeamAttitude::Hostile;
		}
	}

	return ETeamAttitude::Neutral;
}
