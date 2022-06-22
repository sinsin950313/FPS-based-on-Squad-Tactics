// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera\CameraComponent.h"
#include "Interface/FireAttitudeDelegateInterface.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h" 

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
	void ToCommandMode();
public:
	void AttackStart();
	void AttackStop();
private:
	void Kneel();
private:
	bool _bAttackStart = false;
	float _lastAttackTime = 0.0f;
	float _coolTime = 1.0f;
public:
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

private:
	float GetCurrentTime();
private:
	const int _maxMorale = 100;
	const int _minMorale = 0;
	int _morale = 100;
	float _lastMoraleDamagedTime = 0.0f;
	const float _moraleRecoveryStartInterval = 3.0f;
	bool _bMoraleRecoveryStart = true;
	float _lastMoraleRecoveryTime = 0.0f;
	const int _moraleRecoveryValue = 10;
	const float _moraleRecoveryInterval = 1.0f;
public:
	void MoraleAttack(APawn* attacker, int moraleDamage);
	void MoraleRecoveryCheck();
	void MoraleRecovery();

private:
	UPROPERTY(EditAnywhere)
	bool _bShow = false;
};
