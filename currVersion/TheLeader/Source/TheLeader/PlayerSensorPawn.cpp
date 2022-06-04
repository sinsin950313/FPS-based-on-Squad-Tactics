// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSensorPawn.h"
#include "PlayerSensingAIController.h"

// Sets default values
APlayerSensorPawn::APlayerSensorPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = APlayerSensingAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	USceneComponent* sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = sceneComponent;
}

// Called when the game starts or when spawned
void APlayerSensorPawn::BeginPlay()
{
	Super::BeginPlay();
}

//void APlayerSensorPawn::SetDefaultSensor()
//{
//	APlayerSensingAIController* controller = Cast<APlayerSensingAIController>(GetController());
//	controller->SetDefaultSensor();
//}

void APlayerSensorPawn::SetSightConfig(AFPSPawn* pawn)
{
	APlayerSensingAIController* controller = Cast<APlayerSensingAIController>(GetController());
	controller->SetSightConfig(pawn);
}

void APlayerSensorPawn::SetSquadSharedData(SquadSharedData* squadSharedData)
{
	APlayerSensingAIController* controller = Cast<APlayerSensingAIController>(GetController());
	controller->SetSquadSharedData(squadSharedData);
}

void APlayerSensorPawn::SetTeam(UGenericTeamAgent* teamAgent)
{
	APlayerSensingAIController* controller = Cast<APlayerSensingAIController>(GetController());
	controller->SetTeam(teamAgent);
}
