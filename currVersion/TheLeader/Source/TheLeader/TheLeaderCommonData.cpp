// Fill out your copyright notice in the Description page of Project Settings.


#include "TheLeaderCommonData.h"

TheLeaderCommonData::TheLeaderCommonData()
{
}

TheLeaderCommonData::~TheLeaderCommonData()
{
}

int8 GetStateFlagShift(EBotStateFlag flag)
{
	return static_cast<int8>(flag);
}
