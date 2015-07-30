# include "Shader.hpp"

# include "Convert/Convert.hpp"

# include "Window/Window.hpp"

# include <iostream>

Shader::Shader()
	: m_effects()
	, m_current(nullptr)
{

}

Shader& Shader::Instance()
{
	static Shader shader;
	return shader;
}

std::unordered_map<std::wstring, Shader::Effect>& Shader::Effects()
{
	return Instance().m_effects;
}

Shader::Effect*& Shader::Current()
{
	return Instance().m_current;
}

Handle<ID3D11InputLayout>& Shader::InputLayout()
{
	return Instance().m_inputLayout;
}

bool Shader::IsCached(const std::wstring& name)
{
	return Current()->variable.find(name) != Current()->variable.end();
}

ID3DX11EffectVariable* Shader::Cache(const std::wstring& name)
{
	return Current()->variable.at(name);
}

ID3DX11EffectVariable* Shader::Regist(const std::wstring& name)
{
	auto variable = Current()->effect->GetVariableByName(ToMultibyte(name).c_str());
	if (!variable->IsValid())
	{
		throw std::exception("無効な変数です");
	}
	Current()->variable[name] = variable;

	return Cache(name);
}

ID3DX11EffectVariable* Shader::Variable(const std::wstring& name)
{
	if (IsCached(name))
	{
		return Cache(name);
	}

	auto val = Regist(name);

	assert(val && (L"だめです : " + name).c_str());

	return val;
}

Shader::Effect& Shader::Access(const std::wstring& name)
{
	return Effects()[name];
}

void Shader::RegistInputLayout()
{
	if (InputLayout())
	{
		std::cout << "既に入力レイアウトが生成されています" << std::endl;
		return;
	}

	if (Current()->effect == nullptr)
	{
		throw std::exception("シェーダーが指定されていません");
	}

	// 入力レイアウト
	static D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	D3DX11_PASS_DESC passDesc;
	Current()->
		effect->
		GetTechniqueByIndex(0)->
		GetPassByIndex(0)->GetDesc(&passDesc);
	auto hr = Window::Device()->CreateInputLayout(
		layout,
		ARRAYSIZE(layout),
		passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize,
		&InputLayout());
	if (FAILED(hr))
	{
		throw std::exception("入力レイアウトの生成に失敗しました");
	}
	Window::Context()->IASetInputLayout(InputLayout());
}

void Shader::AddShader(const std::wstring& name, const std::wstring& filepath)
{
	if (FAILED(D3DX11CompileEffectFromFile(
		filepath.c_str(),
		NULL,
		NULL,
		0U,
		0U,
		Window::Device(),
		&Access(name).effect,
		NULL)))
	{
		throw std::exception("シェーダーファイルのコンパイルに失敗しました");
	}
}

void Shader::Change(const std::wstring& name)
{
	Current() = &Instance().m_effects.at(name);
}

void Shader::Change(const std::wstring& name, const std::wstring& filepath)
{
	AddShader(name, filepath);
	Change(name);
}

void Shader::Technique(const std::wstring& name)
{
	Current()->technique =
		Current()->effect->GetTechniqueByName(
			ToMultibyte(name).c_str());
	if (!Current()->technique->IsValid())
	{
		throw std::exception("有効なテクニックを取得できませんでした");
	}
}

std::list<Shader::Pass> Shader::Passes()
{
	if (!Current()->technique->IsValid())
	{
		throw std::exception("テクニックが無効です");
	}
	std::list<Shader::Pass> passes;
	D3DX11_TECHNIQUE_DESC techniqueDesc;
	Current()->technique->GetDesc(&techniqueDesc);
	UINT numPasses = techniqueDesc.Passes;
	for (UINT i = 0; i < numPasses; ++i)
	{
		passes.emplace_back(Current()->technique->GetPassByIndex(i));
	}
	return passes;
}

void Shader::SetMatrix(const std::wstring& name, const Matrix& matrix)
{
	Variable(name)->AsMatrix()->SetMatrix(matrix);
}

void Shader::SetVector(const std::wstring& name, const Float4& vector)
{
	Variable(name)->AsVector()->SetFloatVector(vector);
}

void Shader::SetSampler(const std::wstring& name, UINT index, ID3D11SamplerState* sampler)
{
	Variable(name)->AsSampler()->SetSampler(index, sampler);
}

void Shader::SetShaderResource(const std::wstring& name, ID3D11ShaderResourceView* shaderResource)
{
	Variable(name)->AsShaderResource()->SetResource(shaderResource);
}

void Shader::SetScalor(const std::wstring& name, float scalor)
{
	Variable(name)->AsScalar()->SetFloat(scalor);
}

void Shader::SetRenderTargett(const std::wstring& name, ID3D11RenderTargetView* renderTarget)
{
	Variable(name)->AsRenderTargetView()->SetRenderTarget(renderTarget);
}

void Shader::SetRasterizer(const std::wstring& name, UINT index, ID3D11RasterizerState* rasterizer)
{
	Variable(name)->AsRasterizer()->SetRasterizerState(index, rasterizer);
}

void Shader::SetDepthStencilView(const std::wstring& name, ID3D11DepthStencilView* depthStencilView)
{
	Variable(name)->AsDepthStencilView()->SetDepthStencil(depthStencilView);
}

void Shader::SetDepthStencil(const std::wstring& name, UINT index, ID3D11DepthStencilState* depthStencil)
{
	Variable(name)->AsDepthStencil()->SetDepthStencilState(index, depthStencil);
}

void Shader::SetBlend(const std::wstring& name, UINT index, ID3D11BlendState* blendState)
{
	Variable(name)->AsBlend()->SetBlendState(index, blendState);
}
