# pragma once

# include "Handle/Handle.hpp"

# include <unordered_map>

/// <summary>シェーダークラス</summary>
class Shader
{
private:

	/// <summary>エフェクト構造体</summary>
	struct Effect
	{
		Handle<ID3DX11Effect> effect;

		ID3DX11EffectTechnique* technique;

		ID3DX11EffectPass* pass;

		Handle<ID3D11InputLayout> inputLayout;

		std::unordered_map<std::wstring, ID3DX11EffectVariable*> variable;
	};

private:

	Shader();

	static Shader& Instance();

	static bool IsCached(const std::wstring& name);

	static ID3DX11EffectVariable* Cache(const std::wstring& name);

	static ID3DX11EffectVariable* Regist(const std::wstring& name);

	static ID3DX11EffectVariable* Variable(const std::wstring& name);

	static Effect& Access(const std::wstring& name);

	static Effect& Current();

public:

	static void Change(const std::wstring& name);

	static void AddShader(const std::wstring& name, const std::wstring& filepath);

	static void Tech(const std::wstring& name);

	static void Pass(const std::wstring& name);

	static void InputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT num);

	static void Apply();

	static void SetMatrix(const std::wstring& name, const Matrix& matrix);

	static void SetVector(const std::wstring& name, const Float4& vector);

	static void SetSampler(const std::wstring& name, UINT index, ID3D11SamplerState* sampler);

	static void SetShaderResource(const std::wstring& name, ID3D11ShaderResourceView* shaderResource);

	static void SetScalor(const std::wstring& name, float scalor);

	static void SetRenderTargett(const std::wstring& name, ID3D11RenderTargetView* renderTarget);

	static void SetRasterizer(const std::wstring& name, UINT index, ID3D11RasterizerState* rasterizer);

	static void SetDepthStencilView(const std::wstring& name, ID3D11DepthStencilView* depthStencilView);

	static void SetDepthStencil(const std::wstring& name, UINT index, ID3D11DepthStencilState* depthStencil);

private:

	std::unordered_map<std::wstring, Effect> m_effects;

	Effect* m_current;
};
