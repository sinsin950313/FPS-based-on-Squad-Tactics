#include "SightSystemManager.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h" 

SightSystemManager* SightSystemManager::_instance = nullptr;

SightSystemManager::~SightSystemManager()
{
	if (_instance != nullptr)
	{
		delete _instance;
	}
}
SightSystemManager& SightSystemManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new SightSystemManager();
	}
	return *_instance;
}

bool SightSystemManager::IsSpotted(AFPSPawn* target, AFPSPawn* observer)
{
	TArray<FHitResult> hitResults;
	observer->GetWorld()->LineTraceMultiByChannel(hitResults, observer->GetActorLocation(), target->GetActorLocation(), ECollisionChannel::ECC_GameTraceChannel6);
	for (auto iter = hitResults.CreateIterator(); iter; ++iter)
	{
		UE_LOG(LogTemp, Log, TEXT("Sight System Manager - IsSpotted called"));
		return true;
	}
	return false;
}
