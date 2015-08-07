# pragma once

# include "RenderModel.hpp"

# include "Shader/Shader.hpp"

class RenderEnemy : public RenderModel
{
private:

	static const float deltaTime;

public:

	RenderEnemy(Matrix& view, Matrix& projection)
		: RenderModel(aqua::Polygon::Plane())
		, m_view(view)
		, m_projection(projection)
	{

	}

private:

	virtual void OnUpdate() override
	{
		Translate();
	}

	virtual void OnRender() const override
	{
		Shader::Change("Diffuse");
		auto model = Matrix::Transform(m_scale, m_rotate, m_position);
		auto modelView = model * m_view;
		Shader::SetMatrix(L"modelView", modelView);
		Shader::SetMatrix(L"modelViewProjection", modelView * m_projection);
		Shader::SetMatrix(L"normal", modelView.Inverse().Transposed());

		for (auto&& pass : Shader::Passes())
		{
			pass.Apply();
			m_model->Render();
		}
	}

private:

	void Translate()
	{
		if (GetAsyncKeyState('F') != 0)
		{
			m_position.x -= 0.1f * deltaTime;
		}

		if (GetAsyncKeyState('H') != 0)
		{
			m_position.x += 0.1f * deltaTime;
		}

		if (GetAsyncKeyState('T') != 0)
		{
			m_position.z += 0.1f * deltaTime;
		}

		if (GetAsyncKeyState('G') != 0)
		{
			m_position.z -= 0.1f * deltaTime;
		}

		if (GetAsyncKeyState('Y') != 0)
		{
			m_position.y += 0.1f * deltaTime;
		}

		if (GetAsyncKeyState('B') != 0)
		{
			m_position.y -= 0.1f * deltaTime;
		}
	}

private:

	Matrix& m_view;

	Matrix& m_projection;
};

const float RenderEnemy::deltaTime = 0.016667f;
