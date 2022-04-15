// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheLeaderCommonData.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheLeaderPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THELEADER_API ATheLeaderPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATheLeaderPlayerController();
	void changePlayMode(PlayState currPlayState);

protected:
	void BeginPlay() override;

private:
	UPROPERTY()
	APawn* _fpsModePawn;

	UPROPERTY()
	APawn* _commandModePawn;

	void setMouseEnable(bool enable);
};
