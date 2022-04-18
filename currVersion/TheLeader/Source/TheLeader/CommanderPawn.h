// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera\CameraComponent.h"
#include "FPSPawn.h"

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "CommanderPawn.generated.h"

UCLASS()
class THELEADER_API ACommanderPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACommanderPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float val);
	void MoveBackward(float val);
	void MoveLeftSide(float val);
	void MoveRightSide(float val);
	void Turn(float val);
	void ToFPSMode();
	void ToMove();

	UCameraComponent* _cameraComponent;

	TArray<AFPSPawn*> _squadMembers;
};
