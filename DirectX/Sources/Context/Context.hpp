# pragma once

# include "Handle/Handle.hpp"

class Context
{
private:

	Context();

	Context(const Context&);

	Context& operator = (const Context&);

public:

	static Context& Instance()
	{
		static Context context;
		return context;
	}

	operator ID3D11DeviceContext* ()
	{
		return m_context;
	}

private:

	Handle<ID3D11DeviceContext> m_context;
};
