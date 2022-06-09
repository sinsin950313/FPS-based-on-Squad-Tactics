// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera\CameraComponent.h"
#include "FPSPawn.h"
#include "TheLeaderCommonData.h"
#include "FPSAIController.h"
#include "SquadSharedData.h"
#include "PositionPointer.h"

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
	~ACommanderPawn();
	void SetDirection(float yawVal);
private:
	UCameraComponent* _cameraComponent;

	// Called when the game starts or when spawned
protected:
	virtual void BeginPlay() override;
private:
	TArray<AFPSAIController*> _squadMembers;
	UPROPERTY()
	AFPSPawn* _currentLeader;
	void CreateMember(FVector relativeLocation);
	template<typename ToLeader, typename ToMembers>
	void DoIterateToMembers(ToLeader doFunctionWithLeader, ToMembers doFunctionWithMembers);
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
	void LookAt();
	void FireAtWill();
	void HoldFire();

public:
	static const FName kFireAttitude;
	void SetSquadFireAttitude(EBotFireAttitude attitude);
	EBotFireAttitude GetSquadFireAttitude();
private:
	EBotFireAttitude _currentFireAttitude;

private:
	const EPlayerMode _mode = EPlayerMode::COMMODE;

private:
	SquadSharedData* _squadSharedData;

private:
	void UpdateFormation();
	TArray<APositionPointer*> _positionPointers;
};
