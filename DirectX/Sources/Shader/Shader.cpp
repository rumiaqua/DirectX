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

bool Shader::IsCached(const std::wstring& name)
{
	return Current().variable.find(name) != Current().variable.end();
}

ID3DX11EffectVariable* Shader::Cache(const std::wstring& name)
{
	return Current().variable.at(name);
}

ID3DX11EffectVariable* Shader::Regist(const std::wstring& name)
{
	Current().variable[name] =
		Current().effect->GetVariableByName(ToNarrow(name).c_str());

	return Cache(name);
}

ID3DX11EffectVariable* Shader::Variable(const std::wstring& name)
{
	if (IsCached(name))
	{
		return Cache(name);
	}

	auto val = Regist(name);

	assert(val || !(L"だめです : " + name).c_str());

	return val;
}

Shader::Effect& Shader::Access(const std::wstring& name)
{
	return Instance().m_effects[name];
}

Shader::Effect& Shader::Current()
{
	return *Instance().m_current;
}

void Shader::Change(const std::wstring& name)
{
	Instance().m_current = &Instance().m_effects.at(name);
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

void Shader::Tech(const std::wstring& name)
{
	Current().technique =
		Current().effect->GetTechniqueByName(
		ToNarrow(name).c_str());
	if (!Current().technique->IsValid())
	{
		throw std::exception("有効なテクニックを取得できませんでした");
	}
}

std::list<ID3DX11EffectPass*> Shader::Passes()
{
	std::list<ID3DX11EffectPass*> passes;

	D3DX11_TECHNIQUE_DESC techniqueDesc;
	Current().technique->GetDesc(&techniqueDesc);

	for (unsigned int i = 0; i < techniqueDesc.Passes; ++i)
	{
		passes.emplace_back(Current().technique->GetPassByIndex(i));
	}

	InputLayout();

	return passes;
}

void Shader::InputLayout()
{
	if (Instance().m_inputLayout != nullptr)
	{
		std::cout << "既にレイアウトは作成されています" << std::endl;
		return;
	}

	auto pass = Current().technique->GetPassByIndex(0);

	if (pass == nullptr)
	{
		throw std::exception("テクニックが指定されていません");
		return;
	}

	// 入力レイアウト
	static const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// 入力レイアウトの指定
	D3DX11_PASS_DESC passDesc;
	pass->GetDesc(&passDesc);
	Window::Device()->CreateInputLayout(
		layout,
		ARRAYSIZE(layout),
		passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize,
		&Instance().m_inputLayout);
	Window::Context()->IASetInputLayout(Instance().m_inputLayout);
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

void Shader::SetRenderTarget(const std::wstring& name, ID3D11RenderTargetView* renderTarget)
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
