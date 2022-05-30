#include "AISensorManager.h"
#include "Perception/AISenseConfig_Sight.h" 
#include "Interface/AISensorInterface.h"

AISensorManager* AISensorManager::_sensorManager = nullptr;

AISensorManager* AISensorManager::GetInstance()
{
	if (_sensorManager == nullptr)
	{
		_sensorManager = new AISensorManager();
	}
	return _sensorManager;
}

AISensorManager::~AISensorManager()
{
	delete _sensorManager;
}

void AISensorManager::SetDefaultSense(AAIController* aiController)
{
	aiController->SetPerceptionComponent(*NewObject<UAIPerceptionComponent>(aiController, TEXT("PerceptionComponent")));

	UAISenseConfig_Sight* senseConfigSight = NewObject<UAISenseConfig_Sight>(aiController, TEXT("Sight Config"));
	senseConfigSight->SetMaxAge(3);
	aiController->GetPerceptionComponent()->ConfigureSense(*senseConfigSight);

	IAISensorInterface* sensorInterface = Cast<IAISensorInterface>(aiController);
	UAISensingUpdater* sensingUpdater = sensorInterface->GetSensingUpdater();
	aiController->GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(sensingUpdater, &UAISensingUpdater::Sensing);

	aiController->GetPerceptionComponent()->SetDominantSense(*senseConfigSight->GetSenseImplementation());
}

void AISensorManager::SetSightConfig(UAIPerceptionComponent* perceptionComponent)
{
	FAISenseID id = UAISense::GetSenseID(UAISense_Sight::StaticClass());

	if (!id.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("ID does not vaild"));
		return;
	}

	UAISenseConfig* config = perceptionComponent->GetSenseConfig(id);
	if (config == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Sight Sense doesn't exist"));
		return;
	}

	UAISenseConfig_Sight* senseConfigSight = Cast<UAISenseConfig_Sight>(config);

	senseConfigSight->SightRadius = 300;
	senseConfigSight->LoseSightRadius = 600;
	senseConfigSight->PeripheralVisionAngleDegrees = 90;
	senseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	senseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	senseConfigSight->DetectionByAffiliation.bDetectNeutrals = false;
	//Age doesn't work. Setting at create
	//senseConfigSight->SetMaxAge(10);

	perceptionComponent->RequestStimuliListenerUpdate();
}