#pragma once

#include "TheLeaderCommonData.h"

class FireAttitude
{
public:
	EBotFireAttitude GetFireAttitude();
	void SetFireAttitude(EBotFireAttitude attitude);
private:
	EBotFireAttitude _attitude;
};
