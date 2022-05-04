#include "FireAttitude.h"

EBotFireAttitude FireAttitude::GetFireAttitude()
{
	return _attitude;
}

void FireAttitude::SetFireAttitude(EBotFireAttitude attitude)
{
	_attitude = attitude;
}
