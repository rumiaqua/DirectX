# pragma once

# include "Handle/Handle.hpp"

# include "ObjLoader/ObjLoader.hpp"

# include "SimpleVertex/SimpleVertex.hpp"

# include <fstream>

# include "Base/Base.hpp"

float Lerp(float t, float start, float end)
{
	return start + (end - start) * t;
}

class Model
{
public:

	/*
	Handle<ID3D11Buffer> m_vertexBuffer;

	UINT m_stride;

	UINT m_offset;

	Handle<ID3D11Buffer> m_indexBuffer;

	UINT m_numIndices;

	D3D11_PRIMITIVE_TOPOLOGY m_topology;

	Float3 m_position;

	Matrix m_rotateAndScale;
	*/
	Model()
		: m_vertexBuffer()
		, m_stride(0)
		, m_offset(0)
		, m_indexBuffer()
		, m_numIndices(0)
		, m_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		, m_position(0.0f, 0.0f, 0.0f)
		, m_rotateAndScale(DirectX::XMMatrixIdentity())
	{

	}

	void Load(const std::wstring& filename)
	{
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
		Base::Context()->IASetVertexBuffers(
			0U, 1U, &m_vertexBuffer, &m_stride, &m_offset);

		Base::Context()->IASetIndexBuffer(
			m_indexBuffer, DXGI_FORMAT_R16_UINT, 0U);

		Base::Context()->IASetPrimitiveTopology(m_topology);

		Base::Context()->DrawIndexed(
			m_numIndices, 0U, 0);
	}

	void Box()
	{
		static const SimpleVertex v[] =
		{
			// 正面
			{ Float3(-1.0f, -1.0f, -1.0f), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(-1.0f, +1.0f, -1.0f), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+1.0f, +1.0f, -1.0f), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+1.0f, -1.0f, -1.0f), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			// 右
			{ Float3(+1.0f, -1.0f, -1.0f), Float2(0.0f, 0.0f), Float3(1.0f, 0.0f, 0.0f) },
			{ Float3(+1.0f, +1.0f, -1.0f), Float2(0.0f, 1.0f), Float3(1.0f, 0.0f, 0.0f) },
			{ Float3(+1.0f, +1.0f, +1.0f), Float2(1.0f, 1.0f), Float3(1.0f, 0.0f, 0.0f) },
			{ Float3(+1.0f, -1.0f, +1.0f), Float2(1.0f, 0.0f), Float3(1.0f, 0.0f, 0.0f) },
			// 背面
			{ Float3(+1.0f, -1.0f, +1.0f), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f) },
			{ Float3(+1.0f, +1.0f, +1.0f), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, 1.0f) },
			{ Float3(-1.0f, +1.0f, +1.0f), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, 1.0f) },
			{ Float3(-1.0f, -1.0f, +1.0f), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f) },
			// 左
			{ Float3(-1.0f, -1.0f, +1.0f), Float2(0.0f, 0.0f), Float3(-1.0f, 0.0f, 0.0f) },
			{ Float3(-1.0f, +1.0f, +1.0f), Float2(0.0f, 1.0f), Float3(-1.0f, 0.0f, 0.0f) },
			{ Float3(-1.0f, +1.0f, -1.0f), Float2(1.0f, 1.0f), Float3(-1.0f, 0.0f, 0.0f) },
			{ Float3(-1.0f, -1.0f, -1.0f), Float2(1.0f, 0.0f), Float3(-1.0f, 0.0f, 0.0f) },
			// 上
			{ Float3(-1.0f, +1.0f, -1.0f), Float2(0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f) },
			{ Float3(-1.0f, +1.0f, +1.0f), Float2(0.0f, 1.0f), Float3(0.0f, 1.0f, 0.0f) },
			{ Float3(+1.0f, +1.0f, +1.0f), Float2(1.0f, 1.0f), Float3(0.0f, 1.0f, 0.0f) },
			{ Float3(+1.0f, +1.0f, -1.0f), Float2(1.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f) },
			// 下
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

	void Texture()
	{
		static const SimpleVertex v[] =
		{
			{ Float3(0.0f, 0.0f, 0.0f), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(1.0f, 0.0f, 0.0f), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(0.0f, 1.0f, 0.0f), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(1.0f, 1.0f, 0.0f), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
		};

		UINT numVertices = ARRAYSIZE(v);

		static const WORD i[] =
		{
			0, 1, 2, 3,
		};

		UINT numIndices = ARRAYSIZE(i);

		Initialize(
			v,
			numVertices,
			i,
			numIndices,
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
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

		Base::Device()->CreateBuffer(
			&bufferDesc, &initData, &m_vertexBuffer);

		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.ByteWidth = sizeof(WORD) * numIndices;
		initData.pSysMem = indices;

		Base::Device()->CreateBuffer(
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
