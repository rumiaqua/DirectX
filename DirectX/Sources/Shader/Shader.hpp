# pragma once

# include "Handle/Handle.hpp"

# include "Convert/Convert.hpp"

# include <unordered_map>

class Shader
{
private:

	struct Effect
	{
		Handle<ID3DX11Effect> effect;

		ID3DX11EffectTechnique* technique;

		ID3DX11EffectPass* pass;

		Handle<ID3D11InputLayout> inputLayout;

		std::unordered_map<std::wstring, ID3DX11EffectVariable*> variable;
	};

private:

	Shader()
		: m_effects()
		, m_current(nullptr)
	{

	}

	static Shader& Instance()
	{
		static Shader shader;
		return shader;
	}

	static bool IsCached(const std::wstring& name)
	{
		return Current().variable.find(name) != Current().variable.end();
	}

	static ID3DX11EffectVariable* Cache(const std::wstring& name)
	{
		return Current().variable.at(name);
	}

	static ID3DX11EffectVariable* Regist(const std::wstring& name)
	{
		Current().variable[name] =
			Current().effect->GetVariableByName(ToMultibyte(name).c_str());

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

	static Effect& Access(const std::wstring& name)
	{
		return Instance().m_effects[name];
	}

	static Effect& Current()
	{
		return *Instance().m_current;
	}

public:

	static void Change(const std::wstring& name)
	{
		Instance().m_current = &Instance().m_effects.at(name);
	}

	static void AddShader(const std::wstring& name, const std::wstring& filepath)
	{
		D3DX11CompileEffectFromFile(
			filepath.c_str(),
			NULL,
			NULL,
			0U,
			0U,
			Window::Device(),
			&Access(name).effect,
			NULL);
	}

	static void Tech(const std::wstring& name)
	{
		Current().technique =
			Current().effect->GetTechniqueByName(
			ToMultibyte(name).c_str());
	}

	static void Pass(const std::wstring& name)
	{
		Current().pass =
			Current().technique->GetPassByName(
			ToMultibyte(name).c_str());
	}
	static void InputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT num)
	{
		D3DX11_PASS_DESC passDesc;
		Current().pass->GetDesc(&passDesc);
		Window::Device()->CreateInputLayout(
			layout,
			num,
			passDesc.pIAInputSignature,
			passDesc.IAInputSignatureSize,
			&Current().inputLayout);
		Window::Context()->IASetInputLayout(Current().inputLayout);
	}

	static void Apply()
	{
		Current().pass->Apply(0U, Window::Context());
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

	std::unordered_map<std::wstring, Effect> m_effects;

	Effect* m_current;
};
