# pragma once

# include "Handle/Handle.hpp"

# include "ObjLoader/ObjLoader.hpp"

# include "SimpleVertex/SimpleVertex.hpp"

# include "Window/Window.hpp"

# include "Convert/Convert.hpp"

# include "Shader/Shader.hpp"

class Texture2D
{
public:

	Texture2D()
	{

	}

	void Load(const std::wstring& filename)
	{
		DirectX::TexMetadata metadata;
		DirectX::ScratchImage image;

		HRESULT hr = S_OK;

		auto split = Split(filename, '.');

		if (split.back() == L"tga")
		{
			hr = DirectX::LoadFromTGAFile(
				filename.c_str(),
				&metadata,
				image);
		}
		else if (split.back() == L"dds")
		{
			hr = DirectX::LoadFromDDSFile(
				filename.c_str(),
				0U,
				&metadata,
				image);
		}
		else
		{
			hr = DirectX::LoadFromWICFile(
				filename.c_str(),
				0U,
				&metadata,
				image);
		}

		if (FAILED(hr))
		{
			throw std::exception("テクスチャの読込に失敗しました");
		}

		hr = DirectX::CreateShaderResourceView(
			Window::Device(),
			image.GetImages(),
			image.GetImageCount(),
			metadata,
			&m_shaderResource);

		if (FAILED(hr))
		{
			throw std::exception("リソースの生成に失敗しました");
		}

		float width = (float)metadata.width;
		float height = (float)metadata.height;

		static const SimpleVertex v[] =
		{
			// 正面
			{ Float3(0.0f, 0.0f, 0.0f), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(width, 0.0f, 0.0f), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(0.0f, height, 0.0f), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(width, height, 0.0f), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
		};

		UINT numVertices = ARRAYSIZE(v);

		static const unsigned short i[] =
		{
			0, 1, 2, 3,
		};

		UINT numIndices = ARRAYSIZE(i);

		Initialize(v, numVertices, i, numIndices,
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}

	virtual ~Texture2D()
	{

	}

	void Render()
	{
		auto context = Window::Context();

		context->IASetVertexBuffers(
			0U, 1U, &m_vertexBuffer, &m_stride, &m_offset);

		context->IASetIndexBuffer(
			m_indexBuffer, DXGI_FORMAT_R16_UINT, 0U);

		context->IASetPrimitiveTopology(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		Shader::Change(L"Texture");

		static const Matrix Projection =
		{
			2.0f / Window::Width(), 0.0f, 0.0f, 0.0f,
			0.0f, -2.0f / Window::Height(), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f, 1.0f
		};

		Shader::SetMatrix(L"Projection", Projection);
		Shader::SetShaderResource(L"txDiffuse", m_shaderResource);
		Shader::Apply();

		context->DrawIndexed(
			m_numIndices, 0U, 0);
	}

private:

	void Initialize(
		const SimpleVertex* vertices,
		UINT numVertices,
		const WORD* indices,
		UINT numIndices,
		D3D11_PRIMITIVE_TOPOLOGY topology)
	{

		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(initData));

		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.ByteWidth = sizeof(SimpleVertex) * numVertices;
		initData.pSysMem = vertices;

		auto device = Window::Device();

		device->CreateBuffer(
			&bufferDesc, &initData, &m_vertexBuffer);

		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.ByteWidth = sizeof(WORD) * numIndices;
		initData.pSysMem = indices;

		device->CreateBuffer(
			&bufferDesc, &initData, &m_indexBuffer);

		m_stride = sizeof(SimpleVertex);

		m_offset = 0U;

		m_numIndices = numIndices;
	}

private:

	Handle<ID3D11Buffer> m_vertexBuffer;

	UINT m_stride;

	UINT m_offset;

	Handle<ID3D11Buffer> m_indexBuffer;

	UINT m_numIndices;

	Handle<ID3D11ShaderResourceView> m_shaderResource;
};
