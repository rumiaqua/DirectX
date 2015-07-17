# pragma once

# include "Handle/Handle.hpp"

class Texture2D
{
public:

	Texture2D()
	{

	}

	void Load(const std::wstring& filename, ID3D11Device* device, UINT width, UINT height)
	{
		using namespace DirectX;

		TexMetadata metadata;
		ScratchImage image;
		LoadFromDDSFile(filename.c_str(), 0U, &metadata, image);
		CreateShaderResourceView(
			device,
			image.GetImages(),
			image.GetImageCount(),
			metadata,
			&m_texture);

		static Vertex vertices[] =
		{
			{ Float3(0.0f, 0.0f, 0.0f), Float2(0.0f, 0.0f) },
			{ Float3(1.0f, 0.0f, 0.0f), Float2(1.0f, 0.0f) },
			{ Float3(1.0f, 1.0f, 0.0f), Float2(1.0f, 1.0f) },
			{ Float3(0.0f, 1.0f, 0.0f), Float2(0.0f, 1.0f) },
		};

		UINT numVertices = ARRAYSIZE(vertices);

		static WORD indices[] =
		{
			0, 1, 2,
			2, 3, 0,
		};

		UINT numIndices = ARRAYSIZE(indices);

		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(initData));

		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.ByteWidth = sizeof(Vertex) * numVertices;
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
		projection.m11 = 2.0f / width;
		projection.m22 = -2.0f / height;

		Matrix offset = XMMatrixIdentity();
		offset.m41 = -1.0f;
		offset.m42 = 1.0f;

		Matrix composition = projection * offset;

		m_projectionVariable->SetMatrix(composition);

		Matrix identity = XMMatrixIdentity();

		Matrix p = XMMatrixPerspectiveFovLH(
			XM_PIDIV4, 4.0f / 3.0f, 1.0f, 250.0f);

		Matrix v = XMMatrixLookAtLH(
			Float4(0.0f, 3.0f, -6.0f, 1.0f).ToVector(),
			Float4(0.0f, 0.0f, 0.0f, 1.0f).ToVector(),
			Float4(0.0f, 1.0f, 0.0f, 1.0f).ToVector());

		Matrix w = XMMatrixIdentity();

		m_projectionVariable->SetMatrix(identity);

		m_projectionVariable->SetMatrix(w * v * p);
	}

	void Render(ID3D11DeviceContext* context)
	{
		static UINT stride = sizeof(Vertex);
		static UINT offset = 0;

		context->IASetVertexBuffers(
			0U, 1U, &m_vertexBuffer, &stride, &offset);

		context->IASetIndexBuffer(
			m_indexBuffer, DXGI_FORMAT_R16_UINT, 0U);

		context->IASetInputLayout(m_layout);

		context->IASetPrimitiveTopology(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_pass->Apply(0, context);

		context->DrawIndexed(6, 0U, 0);
	}

private:

	struct Vertex
	{
		Float3 position;
		Float2 texcoord;
	};

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
