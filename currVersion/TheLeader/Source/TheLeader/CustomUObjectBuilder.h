#pragma once

class CustomUObjectBuilder
{
public:
	virtual void Build(UObject* param) = 0;
	virtual void clear() = 0;
};
