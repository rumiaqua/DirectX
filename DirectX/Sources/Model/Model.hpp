# pragma once

# include "Handle/Handle.hpp"

# include "ObjLoader/ObjLoader.hpp"

# include "SimpleVertex/SimpleVertex.hpp"

# include "Window/Window.hpp"

# include <fstream>

class Model
{
public:

	Model()
	{

	}

	void Load(const std::wstring& filename)
	{
		HRESULT hr = S_OK;

		ObjLoader loader { filename };

		auto vertices = loader.Vertices();

		auto indices = loader.Indices();

		Initialize(vertices.data(), vertices.size(), indices.data(), indices.size(), loader.Topology());
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

		context->IASetPrimitiveTopology(m_topology);

		context->DrawIndexed(
			m_numIndices, 0U, 0);
	}

	void Box()
	{
		static const SimpleVertex v[] =
		{
			// ����
			{ Float3(-1.0f, -1.0f, -1.0f), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(-1.0f, +1.0f, -1.0f), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+1.0f, +1.0f, -1.0f), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+1.0f, -1.0f, -1.0f), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			// �E
			{ Float3(+1.0f, -1.0f, -1.0f), Float2(0.0f, 0.0f), Float3(1.0f, 0.0f, 0.0f) },
			{ Float3(+1.0f, +1.0f, -1.0f), Float2(0.0f, 1.0f), Float3(1.0f, 0.0f, 0.0f) },
			{ Float3(+1.0f, +1.0f, +1.0f), Float2(1.0f, 1.0f), Float3(1.0f, 0.0f, 0.0f) },
			{ Float3(+1.0f, -1.0f, +1.0f), Float2(1.0f, 0.0f), Float3(1.0f, 0.0f, 0.0f) },
			// �w��
			{ Float3(+1.0f, -1.0f, +1.0f), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f) },
			{ Float3(+1.0f, +1.0f, +1.0f), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, 1.0f) },
			{ Float3(-1.0f, +1.0f, +1.0f), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, 1.0f) },
			{ Float3(-1.0f, -1.0f, +1.0f), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f) },
			// ��
			{ Float3(-1.0f, -1.0f, +1.0f), Float2(0.0f, 0.0f), Float3(-1.0f, 0.0f, 0.0f) },
			{ Float3(-1.0f, +1.0f, +1.0f), Float2(0.0f, 1.0f), Float3(-1.0f, 0.0f, 0.0f) },
			{ Float3(-1.0f, +1.0f, -1.0f), Float2(1.0f, 1.0f), Float3(-1.0f, 0.0f, 0.0f) },
			{ Float3(-1.0f, -1.0f, -1.0f), Float2(1.0f, 0.0f), Float3(-1.0f, 0.0f, 0.0f) },
			// ��
			{ Float3(-1.0f, +1.0f, -1.0f), Float2(0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f) },
			{ Float3(-1.0f, +1.0f, +1.0f), Float2(0.0f, 1.0f), Float3(0.0f, 1.0f, 0.0f) },
			{ Float3(+1.0f, +1.0f, +1.0f), Float2(1.0f, 1.0f), Float3(0.0f, 1.0f, 0.0f) },
			{ Float3(+1.0f, +1.0f, -1.0f), Float2(1.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f) },
			// ��
			{ Float3(-1.0f, -1.0f, +1.0f), Float2(0.0f, 0.0f), Float3(0.0f, -1.0f, 0.0f) },
			{ Float3(-1.0f, -1.0f, -1.0f), Float2(0.0f, 1.0f), Float3(0.0f, -1.0f, 0.0f) },
			{ Float3(+1.0f, -1.0f, -1.0f), Float2(1.0f, 1.0f), Float3(0.0f, -1.0f, 0.0f) },
			{ Float3(+1.0f, -1.0f, +1.0f), Float2(1.0f, 0.0f), Float3(0.0f, -1.0f, 0.0f) },
		};

		UINT numVertices = ARRAYSIZE(v);

		static const unsigned short i[] =
		{
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			8, 9, 10,
			10, 11, 8,

			12, 13, 14,
			14, 15, 12,

			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20,
		};

		UINT numIndices = ARRAYSIZE(i);

		Initialize(v, numVertices, i, numIndices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void Plane()
	{
		static const SimpleVertex v[] =
		{
			// ����
			{ Float3(-1.0f, -1.0f, 0.0f), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(-1.0f, +1.0f, 0.0f), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+1.0f, +1.0f, 0.0f), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+1.0f, -1.0f, 0.0f), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
		};

		UINT numVertices = ARRAYSIZE(v);

		static const unsigned short i[] =
		{
			0, 1, 2,
			2, 3, 0,
		};

		UINT numIndices = ARRAYSIZE(i);

		Initialize(v, numVertices, i, numIndices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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

		m_topology = topology;
	}

private:

	Handle<ID3D11Buffer> m_vertexBuffer;

	UINT m_stride;

	UINT m_offset;

	Handle<ID3D11Buffer> m_indexBuffer;

	UINT m_numIndices;

	D3D11_PRIMITIVE_TOPOLOGY m_topology;

	Float3 m_position;

	Matrix m_rotateAndScale;
};
