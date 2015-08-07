# pragma once

# include "RenderObject.hpp"

# include "Polygon/Polygon.hpp"

# include "Shader/Shader.hpp"

class RenderTempObject final : public RenderObject
{
public:

	RenderTempObject(Matrix& view, Matrix& projection)
		: m_view(view)
		, m_projection(projection)
	{
		m_model = aqua::Polygon::Box();
	}

private:

	virtual void OnUpdate() override
	{

	}

	virtual void OnRender() const override
	{
		Shader::Change(L"Default");
		auto model = Matrix::Transform(m_scale, m_rotate, m_position);
		Shader::SetMatrix(L"modelViewProjection", model * m_view * m_projection);
		Shader::SetVector(L"color", m_color);

		for (auto&& pass : Shader::Passes())
		{
			pass.Apply();
			m_model->Render();
		}
	}

private:

	Matrix& m_view;

	Matrix& m_projection;

	std::shared_ptr<aqua::Polygon> m_model;
};
