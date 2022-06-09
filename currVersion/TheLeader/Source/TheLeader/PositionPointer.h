// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PositionPointerAIController.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PositionPointer.generated.h"

UCLASS(Blueprintable)
class THELEADER_API APositionPointer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APositionPointer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	APositionPointerAIController* _controller;

private:
	FVector _relative;
public:
	void SetRelativeLocation(FVector relative);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector _destination;
public:
	void SetDestination(FVector leaderLocation);

private:
	bool _isPinned;
public:
	void GetBackToFormation();
	void SetPinPosition(FVector location);
};
