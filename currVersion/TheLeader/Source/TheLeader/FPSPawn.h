// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera\CameraComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSPawn.generated.h"

UCLASS()
class THELEADER_API AFPSPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSPawn();

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
	void LookAt(float val);
	void AttackStart();
	void AttackStop();
	void Kneel();
	void ToCommandMode();
	
	bool _bAttackStart = false;
	float _lastAttackTime = 0.0f;
	float _coolTime = 1.0f;
	void Fire();

	enum class EState { STANDUP, KNEEL, PINNED };
	void SetState(EState state);
	EState _currentState = EState::STANDUP;
	float getCurrentMovementCoefficient();

	const float _standUpStateCoefficient = 1.0f;
	const float _kneelStateCoefficient = 0.7;
	const float _pinnedStateCoefficient = 0.3;

	UCameraComponent* _cameraComponent;
};
