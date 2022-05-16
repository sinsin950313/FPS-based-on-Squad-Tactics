#pragma once

#include "InGameControllerInterface.h"

class ControllerBuilder
{
public:
	static ControllerBuilder* GetInstance();
private:
	ControllerBuilder();
	static ControllerBuilder* _instance;

public:
	void Build(AController* controller);
	void Clear();

public:
	ControllerBuilder* InitAttitude(EBotFireAttitude initAttitude);
private:
	EBotFireAttitude _fireAttitude;

public:
	ControllerBuilder* InitTeam(ETeam team);
private:
	FGenericTeamId _team;

public:
	ControllerBuilder* SharedDataSet(SquadSharedData* sharedDataSet);
private:
	SquadSharedData* _squadSharedDataSet;
};
