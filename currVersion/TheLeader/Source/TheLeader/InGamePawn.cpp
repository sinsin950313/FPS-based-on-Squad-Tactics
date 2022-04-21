// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePawn.h"

// Add default functionality here for any IInGamePawn functions that are not pure virtual.

void IInGamePawn::SetPlayMode(EPlayerMode mode)
{
	_currentMode = mode;
}


EPlayerMode IInGamePawn::GetPlayMode() const
{
	return _currentMode;
}
