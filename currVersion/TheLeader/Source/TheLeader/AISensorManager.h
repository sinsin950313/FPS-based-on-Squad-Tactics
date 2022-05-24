#pragma once

#include "Perception/AIPerceptionComponent.h" 
#include "SquadSharedData.h"
#include "AIController.h"

class AISensorManager
{
public:
	static AISensorManager* GetInstance();
	~AISensorManager();
private:
	AISensorManager() = default;
	static AISensorManager* _sensorManager;

public:
	void SetDefaultSense(AAIController* aiController);

public:
	void SetSightConfig(UAIPerceptionComponent* perceptionComponent);
};
