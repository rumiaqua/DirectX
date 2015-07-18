# pragma once

# include <unordered_map>

# include "Handle/Handle.hpp"

# include "Convert/Convert.hpp"

# include "Window/Window.hpp"

class Shader
{
private:

	Shader();

	Shader(const Shader&);

	Shader& operator = (const Shader&);

	Shader& Instance()
	{
		static Shader instance;
		return instance;
	}

public:

	void AddShader(const std::wstring& name, const std::wstring& filepath)
	{
		D3DX11CompileEffectFromFile(
			filepath.c_str(),
			NULL,
			NULL,
			0U,
			0U,
			Window::Device(),
			&m_shaders[name],
			NULL);
	}

	void Change(const std::wstring& name)
	{
		m_current = m_shaders.at(name);
	}

	void Technique(const std::wstring& name)
	{
		m_technique = m_current->GetTechniqueByName(ToMultibyte(name).c_str());
	}

	void SetMatrix(const std::wstring& name, const Matrix& matrix)
	{
		m_current->GetVariableByName(ToMultibyte(name).c_str())
			->AsMatrix()->SetMatrix(matrix);
	}

	void SetShaderResource(const std::wstring& name, ID3D11ShaderResourceView* shaderResource)
	{
		m_current->GetVariableByName(ToMultibyte(name).c_str())
			->AsShaderResource()->SetResource(shaderResource);
	}

	void SetSampler(const std::wstring& name, UINT index, ID3D11SamplerState* sampler)
	{
		m_current->GetVariableByName(ToMultibyte(name).c_str())
			->AsSampler()->SetSampler(index, sampler);
	}

	void SetVector(const std::wstring& name, const Float4& vector)
	{
		m_current->GetVariableByName(ToMultibyte(name).c_str())
			->AsVector()->SetFloatVector(vector);
	}

	void SetScolar(const std::wstring& name, float scalor)
	{
		m_current->GetVariableByName(ToMultibyte(name).c_str())
			->AsScalar()->SetFloat(scalor);
	}

	void Apply()
	{
		m_technique->GetPassByIndex(0)
			->Apply(0U, Window::Context());
	}

private:

	std::unordered_map<const std::wstring&, Handle<ID3DX11Effect>> m_shaders;

	ID3DX11Effect* m_current;

	ID3DX11EffectTechnique* m_technique;
};
