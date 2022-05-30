// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_LookAt.h"

UBT_Service_LookAt::UBT_Service_LookAt()
{
	NodeName = TEXT("Look At");
}

void UBT_Service_LookAt::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
