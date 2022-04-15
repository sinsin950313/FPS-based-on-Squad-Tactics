// Fill out your copyright notice in the Description page of Project Settings.


#include "CommanderPawn.h"
#include "Camera\CameraComponent.h"
#include "TheLeaderPlayerController.h"
#include "TheLeaderCommonData.h"
#include "GameFramework/PawnMovementComponent.h" 

// Sets default values
ACommanderPawn::ACommanderPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = sceneComponent;

	MovementComponent->SetUpdatedComponent(RootComponent);

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	cameraComponent->SetupAttachment(RootComponent);
	cameraComponent->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ACommanderPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACommanderPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACommanderPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//removed for overlapped command like 'e'
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ACommanderPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Backward"), this, &ACommanderPawn::MoveBackward);
	PlayerInputComponent->BindAxis(TEXT("RightSide"), this, &ACommanderPawn::MoveRightSide);
	PlayerInputComponent->BindAxis(TEXT("LeftSide"), this, &ACommanderPawn::MoveLeftSide);

	PlayerInputComponent->BindAxis(TEXT("Command Turn"), this, &ACommanderPawn::Turn);

	PlayerInputComponent->BindAction(TEXT("ToFPS"), EInputEvent::IE_Pressed, this, &ACommanderPawn::ToFPSMode);

	PlayerInputComponent->BindAction(TEXT("ToMove"), EInputEvent::IE_Pressed, this, &ACommanderPawn::ToMove);
}

void ACommanderPawn::MoveForward(float val)
{
	FVector forward = GetActorForwardVector();
	forward.Z = 0;
	forward.Normalize();
	AddMovementInput(forward, val);
}

void ACommanderPawn::MoveBackward(float val)
{
	FVector forward = GetActorForwardVector();
	forward.Z = 0;
	forward.Normalize();
	AddMovementInput(forward, val);
}

void ACommanderPawn::MoveLeftSide(float val)
{
	FVector right = GetActorRightVector();
	right.Z = 0;
	right.Normalize();
	AddMovementInput(right, val);
}

void ACommanderPawn::MoveRightSide(float val)
{
	FVector right = GetActorRightVector();
	right.Z = 0;
	right.Normalize();
	AddMovementInput(right, val);
}

void ACommanderPawn::Turn(float val)
{
	RootComponent->AddRelativeRotation(FRotator(0.0f, val, 0.0f));
}

void ACommanderPawn::ToFPSMode()
{
	ATheLeaderPlayerController* currController = Cast<ATheLeaderPlayerController>(GetController());
	if (currController != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("To FPS Mode"));
		currController->changePlayMode(PlayState::COMMODE);
	}
}

void ACommanderPawn::ToMove()
{
	APlayerController* controller = Cast<APlayerController>(GetController());
	if (controller != nullptr)
	{
		FHitResult hit;
		controller->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel3, false, hit);
		UE_LOG(LogTemp, Log, TEXT("%s"), *hit.Location.ToString());
	}
}
