# pragma once

# include "Handle/Handle.hpp"

class Texture2D
{
public:

	Texture2D()
	{

	}

	void Load(
		const std::wstring& filename, 
		ID3D11Device* device,
		UINT screenWidth,
		UINT screenHeight,
		UINT textureWidth,
		UINT textureHeight)
	{
		using namespace DirectX;

		// 画像読込
		TexMetadata metadata;
		ScratchImage image;
		LoadFromDDSFile(filename.c_str(), 0U, &metadata, image);
		CreateShaderResourceView(
			device,
			image.GetImages(),
			image.GetImageCount(),
			metadata,
			&m_texture);

		// 頂点データ
		static const SimpleVertex vertices[] =
		{
			{ Float3(0.0f, 0.0f, 0.0f), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(150.0f, 0.0f, 0.0f), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(0.0f, 150.0f, 0.0f), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(150.0f, 150.0f, 0.0f), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
		};

		UINT numVertices = ARRAYSIZE(vertices);

		static WORD indices[] =
		{
			0, 1, 2, 3,
		};

		UINT numIndices = ARRAYSIZE(indices);

		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(initData));

		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.ByteWidth = sizeof(SimpleVertex) * numVertices;
		initData.pSysMem = vertices;

		device->CreateBuffer(
			&bufferDesc, &initData, &m_vertexBuffer);

		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.ByteWidth = sizeof(WORD) * numIndices;
		initData.pSysMem = indices;

		device->CreateBuffer(
			&bufferDesc, &initData, &m_indexBuffer);

		auto hr = D3DX11CompileEffectFromFile(
			L"Contents/Texture.fx",
			NULL,
			NULL,
			0U,
			0U,
			device,
			&m_effect,
			NULL);

		m_technique = m_effect->GetTechniqueByName("Default");

		m_pass = m_technique->GetPassByName("P0");

		D3DX11_PASS_DESC passDesc;
		m_pass->GetDesc(&passDesc);

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		UINT numElements = ARRAYSIZE(layout);

		device->CreateInputLayout(
			layout,
			numElements,
			passDesc.pIAInputSignature,
			passDesc.IAInputSignatureSize,
			&m_layout);

		m_projectionVariable =
			m_effect->GetVariableByName("Projection")->AsMatrix();

		m_textureVariable =
			m_effect->GetVariableByName("txDiffuse")->AsShaderResource();

		m_samplerVariable =
			m_effect->GetVariableByName("samLinear")->AsSampler();

		Matrix projection = XMMatrixIdentity();
		projection.m11 = 2.0f / screenWidth;
		projection.m22 = -2.0f / screenHeight;

		Matrix offset = XMMatrixTranslation(-1.0f, 1.0f, 0.0f);

		Matrix composition = projection * offset;

		m_projectionVariable->SetMatrix(composition);
	}

	void Render(ID3D11DeviceContext* context)
	{
		static UINT stride = sizeof(SimpleVertex);
		static UINT offset = 0;

		context->IASetVertexBuffers(
			0U, 1U, &m_vertexBuffer, &stride, &offset);

		context->IASetIndexBuffer(
			m_indexBuffer, DXGI_FORMAT_R16_UINT, 0U);

		// context->IASetInputLayout(m_layout);

		context->IASetPrimitiveTopology(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		m_pass->Apply(0U, context);

		context->DrawIndexed(4, 0U, 0);
	}

private:

	Handle<ID3DX11Effect> m_effect;

	ID3DX11EffectTechnique* m_technique;

	ID3DX11EffectPass* m_pass;

	ID3DX11EffectMatrixVariable* m_projectionVariable;

	ID3DX11EffectShaderResourceVariable* m_textureVariable;

	ID3DX11EffectSamplerVariable* m_samplerVariable;

	Handle<ID3D11Buffer> m_vertexBuffer;

	Handle<ID3D11Buffer> m_indexBuffer;

	Handle<ID3D11ShaderResourceView> m_texture;

	Handle<ID3D11InputLayout> m_layout;
};
