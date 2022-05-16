#include "FireAttitude.h"

EBotFireAttitude UFireAttitude::GetFireAttitude()
{
	return _fireAttitude;
}

void UFireAttitude::SetFireAttitude(EBotFireAttitude fireAttitude)
{
	_fireAttitude = fireAttitude;
}