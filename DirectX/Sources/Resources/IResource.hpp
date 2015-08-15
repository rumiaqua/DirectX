# pragma once

class IResource
{
public:

	virtual ~IResource()
	{

	}

public:

	virtual bool Load(const String& name) = 0;
};
