# pragma once

# include "Handle/Handle.hpp"

class Device
{
private:

	Device();

	Device(const Device&);

	Device& operator = (const Device&);

public:

	static Device& Instance()
	{
		static Device device;
		return device;
	}

	void Initialize()
	{

	}

	operator ID3D11Device* ()
	{
		return m_device;
	}

private:

	Handle<ID3D11Device> m_device;
};
