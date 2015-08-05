# pragma once

# include "Handle/Handle.hpp"

# include <unordered_map>

# include "Window/Window.hpp"

/// <summary>シェーダークラス</summary>
class Shader
{
private:

	/// <summary>エフェクト構造体</summary>
	struct Effect
	{
		Handle<ID3DX11Effect> effect;

		ID3DX11EffectTechnique* technique;

		std::unordered_map<String, ID3DX11EffectVariable*> variable;
	};

public:

	class Pass
	{
	public:
		Pass(ID3DX11EffectPass* pass)
			: m_pass(pass)
		{

		}
		void Apply() const
		{
			m_pass->Apply(0U, Window::Context());
		}
	private:
		ID3DX11EffectPass* m_pass;
	};

private:

	Shader();

	static Shader& Instance();

	static std::unordered_map<String, Effect>& Effects();

	static Effect*& Current();

	static Handle<ID3D11InputLayout>& InputLayout();

	static bool IsCached(const String& name);

	static ID3DX11EffectVariable* Cache(const String& name);

	static ID3DX11EffectVariable* Regist(const String& name);

	static ID3DX11EffectVariable* Variable(const String& name);

	static Effect& Access(const String& name);

public:

	static void RegistInputLayout();

	static void AddShader(const String& name, const String& filepath);

	static void Change(const String& name);

	static void Change(const String& name, const String& filepath);

	static void Technique(const String& name);

	static std::list<Pass> Passes();

	static void SetMatrix(const String& name, const Matrix& matrix);

	static void SetVector(const String& name, const Vector4& vector);

	static void SetSampler(const String& name, UINT index, ID3D11SamplerState* sampler);

	static void SetShaderResource(const String& name, ID3D11ShaderResourceView* shaderResource);

	static void SetScalor(const String& name, float scalor);

	static void SetRenderTargett(const String& name, ID3D11RenderTargetView* renderTarget);

	static void SetRasterizer(const String& name, UINT index, ID3D11RasterizerState* rasterizer);

	static void SetDepthStencilView(const String& name, ID3D11DepthStencilView* depthStencilView);

	static void SetDepthStencil(const String& name, UINT index, ID3D11DepthStencilState* depthStencil);

	static void SetBlend(const String& name, UINT index, ID3D11BlendState* blendState);

private:

	std::unordered_map<String, Effect> m_effects;

	Effect* m_current;

	Handle<ID3D11InputLayout> m_inputLayout;
};
