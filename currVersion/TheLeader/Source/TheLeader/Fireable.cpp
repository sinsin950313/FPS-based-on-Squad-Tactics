// Fill out your copyright notice in the Description page of Project Settings.


#include "Fireable.h"

// Add default functionality here for any IFireable functions that are not pure virtual.
IFireable::IFireable()
{
	_currentAttitude = EBotFireAttitude::FIREATWILL;
}

void IFireable::SetFireAttitude(EBotFireAttitude attitude)
{
	UE_LOG(LogTemp, Log, TEXT("Call Set Fire Attitude"))
	_currentAttitude = attitude;
}

EBotFireAttitude IFireable::GetFireAttitude()
{
	return _currentAttitude;
}

bool IFireable::IsAttack()
{
	return _currentAttitude == EBotFireAttitude::FIREATWILL;
}
