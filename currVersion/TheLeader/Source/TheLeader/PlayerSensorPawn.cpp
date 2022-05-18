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
