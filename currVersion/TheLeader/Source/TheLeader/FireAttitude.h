#pragma once

#include "TheLeaderCommonData.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FireAttitude.generated.h"

UCLASS()
class THELEADER_API UFireAttitude : public UObject
{
	GENERATED_BODY()
private:
	EBotFireAttitude _fireAttitude;
public:
	EBotFireAttitude GetFireAttitude();
	void SetFireAttitude(EBotFireAttitude fireAttitude);
};
