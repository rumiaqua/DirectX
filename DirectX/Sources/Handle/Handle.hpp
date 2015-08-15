# pragma once

# include <exception>

template <typename Type>
class Handle
{
public:

	Handle()
		: Handle(nullptr)
	{

	}

	Handle(Type* handle)
		: m_handle(handle)
	{
		static_cast<IUnknown*>(m_handle);
	}

	virtual ~Handle()
	{
		Release();
	}

	operator Type*()
	{
		return Pointer();
	}

	operator const Type*() const
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

	const Type* operator -> () const
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

	const Type* Pointer() const
	{
		return m_handle;
	}

	Type** Double()
	{
		return &m_handle;
	}

	void Release()
	{
		if (m_handle)
		{
			m_handle->Release();
			m_handle = nullptr;
		}
	}

protected:

	Type* m_handle;
};
