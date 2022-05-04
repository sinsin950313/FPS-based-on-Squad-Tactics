#include "InGameController.h"

InGameController::ControllerBuilder InGameController::_builder;

void InGameController::SetFireAttitude(EBotFireAttitude attitude)
{
	_attitude.SetFireAttitude(attitude);
}

EBotFireAttitude InGameController::GetFireAttitude()
{
	return _attitude.GetFireAttitude();
}

EBelonged InGameController::GetBelonged()
{
	return _belonged;
}

InGameController::InGameController()
{
	Builder().Build(this);
}

InGameController::ControllerBuilder& InGameController::Builder()
{
	_builder.clear();
	return _builder;
}

InGameController::ControllerBuilder::ControllerBuilder()
{
	clear();
}

void InGameController::ControllerBuilder::Build(InGameController* controller)
{
	controller->_attitude.SetFireAttitude(_attitude);
	controller->_belonged = _belonged;

	clear();
}

void InGameController::ControllerBuilder::clear()
{
	_attitude = EBotFireAttitude::FIREATWILL;
	_belonged = EBelonged::ENEMY;
}

InGameController::ControllerBuilder& InGameController::ControllerBuilder::FireAttitude(EBotFireAttitude attitude)
{
	_attitude = attitude;
	return *this;
}

InGameController::ControllerBuilder& InGameController::ControllerBuilder::Belonged(EBelonged belonged)
{
	_belonged = belonged;
	return *this;
}
