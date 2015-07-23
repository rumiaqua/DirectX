# pragma once

# include "Handle/Handle.hpp"

# include "Convert/Convert.hpp"

# include <unordered_map>

class Shader
{
private:

	Shader()
		: m_effect(nullptr)
	{

	}

	static Shader& Instance()
	{
		static Shader shader;
		return shader;
	}

	static bool IsCached(const std::wstring& name)
	{
		return Instance().m_variable.find(name) != Instance().m_variable.end();
	}

	static ID3DX11EffectVariable* Cache(const std::wstring& name)
	{
		return Instance().m_variable.at(name);
	}

	static ID3DX11EffectVariable* Regist(const std::wstring& name)
	{
		Instance().m_variable[name] =
			Instance().m_effect->GetVariableByName(ToMultibyte(name).c_str());

		return Cache(name);
	}

	static ID3DX11EffectVariable* Variable(const std::wstring& name)
	{
		if (IsCached(name))
		{
			return Cache(name);
		}
		else
		{
			auto val =Regist(name);
			if (!val)
			{
				assert((L"‚¾‚ß‚Å‚· : " + name).c_str());
			}
			return val;
		}
	}

public:

	static void SetEffect(const std::wstring& filepath)
	{
		D3DX11CompileEffectFromFile(
			filepath.c_str(),
			NULL,
			NULL,
			0U,
			0U,
			Window::Device(),
			&Instance().m_effect,
			NULL);
	}

	static void Tech(const std::wstring& name)
	{
		Instance().m_technique =
			Instance().m_effect->GetTechniqueByName(
			ToMultibyte(name).c_str());
	}

	static void Pass(const std::wstring& name)
	{
		Instance().m_pass = Instance().m_technique->GetPassByName(
			ToMultibyte(name).c_str());
	}
	static void InputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT num)
	{
		D3DX11_PASS_DESC passDesc;
		Instance().m_pass->GetDesc(&passDesc);
		Window::Device()->CreateInputLayout(
			layout,
			num,
			passDesc.pIAInputSignature,
			passDesc.IAInputSignatureSize,
			&Instance().m_inputLayout);
		Window::Context()->IASetInputLayout(Instance().m_inputLayout);
	}

	static void Apply()
	{
		Instance().m_pass->Apply(0U, Window::Context());
	}


	static void SetMatrix(const std::wstring& name, const Matrix& matrix)
	{
		Variable(name)->AsMatrix()->SetMatrix(matrix);
	}

	static void SetVector(const std::wstring& name, const Float4& vector)
	{
		Variable(name)->AsVector()->SetFloatVector(vector);
	}

	static void SetSampler(const std::wstring& name, UINT index, ID3D11SamplerState* sampler)
	{
		Variable(name)->AsSampler()->SetSampler(index, sampler);
	}

	static void SetShaderResource(const std::wstring& name, ID3D11ShaderResourceView* shaderResource)
	{
		Variable(name)->AsShaderResource()->SetResource(shaderResource);
	}

	static void SetScalor(const std::wstring& name, float scalor)
	{
		Variable(name)->AsScalar()->SetFloat(scalor);
	}

	static void SetRenderTargett(const std::wstring& name, ID3D11RenderTargetView* renderTarget)
	{
		Variable(name)->AsRenderTargetView()->SetRenderTarget(renderTarget);
	}

	static void SetRasterizer(const std::wstring& name, UINT index, ID3D11RasterizerState* rasterizer)
	{
		Variable(name)->AsRasterizer()->SetRasterizerState(index, rasterizer);
	}

	static void SetDepthStencilView(const std::wstring& name, ID3D11DepthStencilView* depthStencilView)
	{
		Variable(name)->AsDepthStencilView()->SetDepthStencil(depthStencilView);
	}

	static void SetDepthStencil(const std::wstring& name, UINT index, ID3D11DepthStencilState* depthStencil)
	{
		Variable(name)->AsDepthStencil()->SetDepthStencilState(index, depthStencil);
	}

private:

	Handle<ID3DX11Effect> m_effect;

	ID3DX11EffectTechnique* m_technique;

	ID3DX11EffectPass* m_pass;

	Handle<ID3D11InputLayout> m_inputLayout;

	std::unordered_map<std::wstring, ID3DX11EffectVariable*> m_variable;
};
