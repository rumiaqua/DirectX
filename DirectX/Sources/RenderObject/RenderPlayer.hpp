# pragma once

# include "RenderModel.hpp"

# include "Shader/Shader.hpp"

class RenderPlayer : public RenderModel
{
private:

	static const float deltaTime;

public:

	RenderPlayer(Matrix& view, Matrix& projection)
		: RenderModel(std::make_shared<aqua::Model>(L"Contents/Box.obj"))
		, m_view(view)
		, m_projection(projection)
	{

	}

private:

	virtual void OnUpdate() override
	{
		Scale();
		Rotate();
		Translate();
	}

	virtual void OnRender() const override
	{
		Shader::Change("Default");
		auto model = Matrix::Transform(m_scale, m_rotate, m_position);
		Shader::SetMatrix("modelViewProjection", model * m_view * m_projection);

		for (auto&& pass : Shader::Passes())
		{
			pass.Apply();
			m_model->Render();
		}
	}

private:

	void Rotate()
	{
		float angle = 0.0f;
		if (GetAsyncKeyState(VK_LEFT) != 0)
		{
			angle -= Math::Radian * deltaTime;
		}
		if (GetAsyncKeyState(VK_RIGHT) != 0)
		{
			angle += Math::Radian * deltaTime;
		}

		m_rotate = m_rotate.Yaw(angle);
	}

	void Translate()
	{
		if (GetAsyncKeyState('A') != 0)
		{
			m_position.x -= 0.1f * deltaTime;
		}

		if (GetAsyncKeyState('D') != 0)
		{
			m_position.x += 0.1f * deltaTime;
		}

		if (GetAsyncKeyState('W') != 0)
		{
			m_position.z += 0.1f * deltaTime;
		}

		if (GetAsyncKeyState('S') != 0)
		{
			m_position.z -= 0.1f * deltaTime;
		}

		if (GetAsyncKeyState('E') != 0)
		{
			m_position.y += 0.1f * deltaTime;
		}

		if (GetAsyncKeyState('X') != 0)
		{
			m_position.y -= 0.1f * deltaTime;
		}
	}

	void Scale()
	{
		if (GetAsyncKeyState('Q') != 0)
		{
			m_scale *= 0.50f * deltaTime;
		}
		if (GetAsyncKeyState('Z') != 0)
		{
			m_scale *= 1.50f * deltaTime;
		}
	}

private:

	Matrix& m_view;

	Matrix& m_projection;
};

const float RenderPlayer::deltaTime = 0.016667f;
