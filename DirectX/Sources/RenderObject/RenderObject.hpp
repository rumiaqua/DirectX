# pragma once

# include "OrderedRender/OrderedRender.hpp"

class RenderObject
{
public:

	RenderObject() = default;

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
