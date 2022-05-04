#include "FireAttitude.h"

EBotFireAttitude UFireAttitude::GetFireAttitude()
{
	return _attitude;
}

void UFireAttitude::SetFireAttitude(EBotFireAttitude attitude)
{
	UE_LOG(LogTemp, Log, TEXT("Called SetFireAttitude"));
	_attitude = attitude;
}
