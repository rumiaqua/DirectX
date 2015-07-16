# pragma once

# include "Reference/Reference.hpp"

template <typename Type>
class Handle : public Reference<Type>
{
public:

	Handle()
		: Handle(nullptr)
	{

	}

	Handle(Type* handle)
		: Reference(handle)
	{

	}

	virtual ~Handle()
	{
		Release();
	}

private:

	void Release()
	{
		if (m_handle)
		{
			m_handle->Release();
			m_handle = nullptr;
		}
	}
};
