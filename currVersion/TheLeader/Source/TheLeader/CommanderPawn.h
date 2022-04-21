// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera\CameraComponent.h"
#include "FPSPawn.h"
#include "TheLeaderCommonData.h"
#include "FPSAIController.h"
#include "InGamePawn.h"

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "CommanderPawn.generated.h"

UCLASS()
class THELEADER_API ACommanderPawn : public ADefaultPawn, public IInGamePawn
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
	UPROPERTY()
	AFPSPawn* _currentLeader;
	void DoIterateToMembers(TFunction<void(IFireable*)> func);
public:
	AFPSPawn* GetLeader();

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
	static const FName kFireAttitude;
	void ChangeSquadFireAttitude(EBotFireAttitude attitude);
	EBotFireAttitude GetSquadFireAttitude();
private:
	EBotFireAttitude _currentFireAttitude;
};
