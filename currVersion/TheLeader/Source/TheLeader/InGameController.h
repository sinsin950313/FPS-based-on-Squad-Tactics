#pragma once

#include "TheLeaderCommonData.h"
#include "CustomUObjectBuilder.h"
#include "FireAttitude.h"

class InGameController
{
public:
	InGameController();

public:
	class ControllerBuilder
	{
	public:
		ControllerBuilder();
		void Build(InGameController* controller);
		void clear();

	public:
		ControllerBuilder& FireAttitude(EBotFireAttitude attitude);
	private:
		EBotFireAttitude _attitude;

	public:
		ControllerBuilder& Belonged(EBelonged belonged);
	private:
		EBelonged _belonged;
	};
	static ControllerBuilder& Builder();
private:
	static ControllerBuilder _builder;

public:
	virtual void SetFireAttitude(EBotFireAttitude attitude);
	EBotFireAttitude GetFireAttitude();
private:
	FireAttitude _attitude;

public:
	EBelonged GetBelonged();
private:
	EBelonged _belonged;
};
