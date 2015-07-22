# pragma once

# include "Handle/Handle.hpp"

# include "ObjLoader/ObjLoader.hpp"

# include "SimpleVertex/SimpleVertex.hpp"

# include "Window/Window.hpp"

# include <fstream>

# include "Shader/Shader.hpp"

class Model
{
public:

	Model()
	{

	}

	void Load(const std::wstring& filename, UINT width, UINT height)
	{
		static const SimpleVertex vertices[] =
		{
			// ³–Ê
			{ Float3(-1.0f, -1.0f, 0.0f), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(-1.0f, +1.0f, 0.0f), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+1.0f, +1.0f, 0.0f), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+1.0f, -1.0f, 0.0f), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
		};

		UINT numVertices = ARRAYSIZE(vertices);

		static const unsigned short indices[] =
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
	}

	virtual ~Model()
	{

	}

	void Render()
	{
		auto context = Window::Context();

		context->IASetVertexBuffers(
			0U, 1U, &m_vertexBuffer, &m_stride, &m_offset);

		context->IASetIndexBuffer(
			m_indexBuffer, DXGI_FORMAT_R16_UINT, 0U);

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		static Matrix projection
		{
			2.0f / Window::Width(), 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / Window::Height(), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		Shader::SetMatrix(L"Projection", projection);

		context->DrawIndexed(
			m_numIndices, 0U, 0);
	}

private:

	Handle<ID3D11Buffer> m_vertexBuffer;

	UINT m_stride;

	UINT m_offset;

	Handle<ID3D11Buffer> m_indexBuffer;

	UINT m_numIndices;
};
