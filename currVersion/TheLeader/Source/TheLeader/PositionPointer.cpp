// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionPointer.h"
#include "Components\CapsuleComponent.h"

// Sets default values
APositionPointer::APositionPointer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = APositionPointerAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PositionPointer"));

	_isPinned = false;

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshLoader(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (meshLoader.Succeeded())
	{
		UStaticMeshComponent* meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
		meshComponent->SetupAttachment(RootComponent);
		AddOwnedComponent(meshComponent);
		meshComponent->SetStaticMesh(meshLoader.Object);
		meshComponent->SetWorldScale3D(FVector(0.1f));
		meshComponent->SetCollisionProfileName(TEXT("PositionPointer"));
	}
}

// Called when the game starts or when spawned
void APositionPointer::BeginPlay()
{
	Super::BeginPlay();
	
	_controller = Cast<APositionPointerAIController>(GetController());
}

void APositionPointer::SetRelativeLocation(FVector relative)
{
	_relative = relative;
}

// Called every frame
void APositionPointer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_controller->SetDestination(_destination);
}

void APositionPointer::SetDestination(FVector leaderLocation)
{
	if (!_isPinned)
	{
		_destination = leaderLocation + _relative;
	}
}

void APositionPointer::GetBackToFormation()
{
	_isPinned = false;
}

void APositionPointer::SetPinPosition(FVector location)
{
	_isPinned = true;
	_destination = location;
}
