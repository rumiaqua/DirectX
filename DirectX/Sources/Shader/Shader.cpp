# include "Shader.hpp"

# include "Convert/Convert.hpp"

# include "Window/Window.hpp"

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
		Current().effect->GetVariableByName(ToMultibyte(name).c_str());

	return Cache(name);
}

ID3DX11EffectVariable* Shader::Variable(const std::wstring& name)
{
	if (IsCached(name))
	{
		return Cache(name);
	}

	auto val = Regist(name);

	assert(val && (L"‚¾‚ß‚Å‚· : " + name).c_str());

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

void Shader::Tech(const std::wstring& name)
{
	Current().technique =
		Current().effect->GetTechniqueByName(
		ToMultibyte(name).c_str());
}

void Shader::Pass(const std::wstring& name)
{
	Current().pass =
		Current().technique->GetPassByName(
		ToMultibyte(name).c_str());
}
void Shader::InputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT num)
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

void Shader::Apply()
{
	Current().pass->Apply(0U, Window::Context());
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
