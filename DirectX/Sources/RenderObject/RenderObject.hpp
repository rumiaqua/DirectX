# pragma once

# include "OrderedRender/OrderedRender.hpp"

class RenderObject
{
public:

	RenderObject()
		: m_position(Vector3::Zero)
		, m_rotate(Quaternion::Identity())
		, m_scale(Vector3::One)
		, m_color(Vector4::One)
	{

	}

	virtual ~RenderObject()
	{

	}

	void Update()
	{
		OnUpdate();
	}

	void Render() const
	{
		OrderedRender::Regist(m_color.a, m_position.z,
			std::bind(&RenderObject::OnRender, this));
	}

private:

	virtual void OnUpdate() = 0;

	virtual void OnRender() const = 0;

protected:

	Vector3 m_position;

	Quaternion m_rotate;

	Vector3 m_scale;

	Vector4 m_color;
};
