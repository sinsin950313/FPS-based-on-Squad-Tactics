#pragma once

#include "TheLeaderCommonData.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FireAttitude.generated.h"

UCLASS()
class UFireAttitude : public UObject
{
	GENERATED_BODY()

public:
	EBotFireAttitude GetFireAttitude();
	void SetFireAttitude(EBotFireAttitude attitude);
private:
	EBotFireAttitude _attitude;
};
