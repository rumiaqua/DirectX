# pragma once

template <typename Type>
class Optional
{
public:

	explicit Optional()
		: m_initialized(false)
	{

	}

	~Optional()
	{

	}

public:

	operator bool() const
	{
		return m_initialized;
	}

	Optional<Type>& operator = (const Type& value)
	{
		m_value = value;

		m_initialized = true;

		return *this;
	}

	const Type& operator * () const
	{
		return m_value;
	}

	Type& operator * ()
	{
		return m_value;
	}

	Type* operator -> () const
	{
		return &m_value;
	}

private:

	Type m_value;

	bool m_initialized;
};
