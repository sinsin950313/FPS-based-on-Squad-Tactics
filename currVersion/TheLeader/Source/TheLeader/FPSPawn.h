// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera\CameraComponent.h"
#include "FireAttitudeDelegateInterface.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSPawn.generated.h"

UCLASS()
class THELEADER_API AFPSPawn : public ACharacter, public IFireAttitudeDelegateInterface
{
	GENERATED_BODY()

	// Sets default values for this character's properties
public:
	AFPSPawn();
private:
	UCameraComponent* _cameraComponent;

	// Called when the game starts or when spawned
protected:
	virtual void BeginPlay() override;

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
	void LookAt(float val);
	void AttackStart();
	void AttackStop();
	void Kneel();
	void ToCommandMode();
private:
	bool _bAttackStart = false;
	float _lastAttackTime = 0.0f;
	float _coolTime = 1.0f;
	void Fire();
private:
	enum class EState { STANDUP, KNEEL, PINNED };
	void SetState(EState state);
	EState _currentState = EState::STANDUP;
private:
	const float _kStandUpStateCoefficient = 1.0f;
	const float _kKneelStateCoefficient = 0.7;
	const float _kPinnedStateCoefficient = 0.3;
	float GetCurrentMovementCoefficient();

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
private:
	int _HP = 100;

private:
	const EPlayerMode _mode = EPlayerMode::FPSMODE;
};
