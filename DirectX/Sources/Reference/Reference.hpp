# pragma once

# include <exception>

template <typename Type>
class Reference
{
public:

	Reference()
		: Reference(nullptr)
	{
		
	}

	Reference(Type* handle)
		: m_handle(handle)
	{
		static_cast<IUnknown*>(m_handle);
	}

	virtual ~Reference()
	{

	}

	operator Type*()
	{
		return Pointer();
	}

	operator bool() const
	{
		return m_handle != nullptr;
	}

	Type* operator -> ()
	{
		return Pointer();
	}

	Type** operator & ()
	{
		return Double();
	}

public:

	Type* Pointer()
	{
		return m_handle;
	}

	Type** Double()
	{
		return &m_handle;
	}

protected:

	Type* m_handle;
};
