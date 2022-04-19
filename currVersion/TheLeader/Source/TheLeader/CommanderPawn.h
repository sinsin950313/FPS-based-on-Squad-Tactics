// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera\CameraComponent.h"
#include "FPSPawn.h"
#include "TheLeaderCommonData.h"
#include "FPSAIController.h"

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "CommanderPawn.generated.h"

UCLASS()
class THELEADER_API ACommanderPawn : public ADefaultPawn
{
	GENERATED_BODY()

	// Sets default values for this pawn's properties
public:
	ACommanderPawn();
private:
	UCameraComponent* _cameraComponent;

	// Called when the game starts or when spawned
protected:
	virtual void BeginPlay() override;
private:
	TArray<AFPSAIController*> _squadMembers;

	// Called every frame
public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void MoveForward(float val);
	void MoveBackward(float val);
	void MoveLeftSide(float val);
	void MoveRightSide(float val);
	void Turn(float val);
	void ToFPSMode();
	void ToMove();

public:
	EBotFireAttitude getAttitude();
	void setAttitude(EBotFireAttitude attitude);
private:
	EBotFireAttitude _currentAttitude;

public:
	static const FName FireAttitude;

public:
	void bindAttitude();
private:
	bool bIsBinded = false;

public:
	void changeFireAttitude(EBotFireAttitude attitude);
};
