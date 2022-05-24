#include "ControllerBuilder.h"

ControllerBuilder* ControllerBuilder::_instance = nullptr;

ControllerBuilder* ControllerBuilder::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ControllerBuilder();
	}
	UE_LOG(LogTemp, Warning, TEXT("Controller Builder have to change from Singleton to GameInstance"));
	return _instance;
}

ControllerBuilder::ControllerBuilder()
{
	Clear();
}

void ControllerBuilder::Build(AController* controller)
{
	IInGameControllerInterface* inGameControllerInterface = Cast<IInGameControllerInterface>(controller);
	if (inGameControllerInterface != nullptr)
	{
		inGameControllerInterface->SetGenericTeamId(_team);
		inGameControllerInterface->SetFireAttitude(_fireAttitude);
		inGameControllerInterface->SetSquadSharedData(_squadSharedDataSet);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("InGameController not Castable"));
	}

	Clear();
}

void ControllerBuilder::Clear()
{
	_fireAttitude = EBotFireAttitude::FIREATWILL;
	_team = FGenericTeamId(ETeam::ENEMY);
	_squadSharedDataSet = nullptr;
}

ControllerBuilder* ControllerBuilder::InitAttitude(EBotFireAttitude initAttitude)
{
	_fireAttitude = initAttitude;
	return GetInstance();
}

ControllerBuilder* ControllerBuilder::InitTeam(ETeam team)
{
	_team = team;
	return GetInstance();
}

ControllerBuilder* ControllerBuilder::SharedDataSet(SquadSharedData* sharedDataSet)
{
	_squadSharedDataSet = sharedDataSet;
	return this;
}
