#pragma once

#include "FPSPawn.h"

class SightSystemManager
{
private:
	SightSystemManager() = default;
	static SightSystemManager* _instance;
public:
	~SightSystemManager();
	static SightSystemManager& GetInstance();
	bool IsSpotted(AFPSPawn* target, AFPSPawn* observer);
};
