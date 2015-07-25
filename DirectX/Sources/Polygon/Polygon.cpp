# include "Polygon.hpp"

# include "Vertex/Vertex.hpp"

# include "Window/Window.hpp"

# include <memory>

# include "Shader/Shader.hpp"

namespace aqua
{
	Polygon::Polygon()
		: m_vertexBuffer()
		, m_stride(0U)
		, m_offset(0U)
		, m_indexBuffer()
		, m_numIndices(0U)
		, m_topology()
	{

	}

	Polygon::~Polygon()
	{

	}

	std::shared_ptr<Polygon> Polygon::Box(float size)
	{
		float width = size;
		static const Vertex vertices[] =
		{
			// 正面
			{ Float3(-width, -width, -width), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(-width, +width, -width), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+width, +width, -width), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+width, -width, -width), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			// 右
			{ Float3(+width, -width, -width), Float2(0.0f, 0.0f), Float3(1.0f, 0.0f, 0.0f) },
			{ Float3(+width, +width, -width), Float2(0.0f, 1.0f), Float3(1.0f, 0.0f, 0.0f) },
			{ Float3(+width, +width, +width), Float2(1.0f, 1.0f), Float3(1.0f, 0.0f, 0.0f) },
			{ Float3(+width, -width, +width), Float2(1.0f, 0.0f), Float3(1.0f, 0.0f, 0.0f) },
			// 背面
			{ Float3(+width, -width, +width), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f) },
			{ Float3(+width, +width, +width), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, 1.0f) },
			{ Float3(-width, +width, +width), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, 1.0f) },
			{ Float3(-width, -width, +width), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f) },
			// 左
			{ Float3(-width, -width, +width), Float2(0.0f, 0.0f), Float3(-1.0f, 0.0f, 0.0f) },
			{ Float3(-width, +width, +width), Float2(0.0f, 1.0f), Float3(-1.0f, 0.0f, 0.0f) },
			{ Float3(-width, +width, -width), Float2(1.0f, 1.0f), Float3(-1.0f, 0.0f, 0.0f) },
			{ Float3(-width, -width, -width), Float2(1.0f, 0.0f), Float3(-1.0f, 0.0f, 0.0f) },
			// 上
			{ Float3(-width, +width, -width), Float2(0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f) },
			{ Float3(-width, +width, +width), Float2(0.0f, 1.0f), Float3(0.0f, 1.0f, 0.0f) },
			{ Float3(+width, +width, +width), Float2(1.0f, 1.0f), Float3(0.0f, 1.0f, 0.0f) },
			{ Float3(+width, +width, -width), Float2(1.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f) },
			// 下
			{ Float3(-width, -width, +width), Float2(0.0f, 0.0f), Float3(0.0f, -1.0f, 0.0f) },
			{ Float3(-width, -width, -width), Float2(0.0f, 1.0f), Float3(0.0f, -1.0f, 0.0f) },
			{ Float3(+width, -width, -width), Float2(1.0f, 1.0f), Float3(0.0f, -1.0f, 0.0f) },
			{ Float3(+width, -width, +width), Float2(1.0f, 0.0f), Float3(0.0f, -1.0f, 0.0f) },
		};

		UINT numVertices = ARRAYSIZE(vertices);

		static const unsigned short indices[] =
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

		UINT numIndices = ARRAYSIZE(indices);

		auto polygon = std::make_shared<Polygon>();

		polygon->Initialize(
			vertices,
			numVertices,
			indices,
			numIndices,
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		return polygon;
	}

	std::shared_ptr<Polygon> Polygon::Plane(float size, bool isBoth)
	{
		float width = size;
		static const Vertex HalfVertices[] =
		{
			// 正面
			{ Float3(-width, -width, 0.0f), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(-width, +width, 0.0f), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+width, +width, 0.0f), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+width, -width, 0.0f), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
		};

		static UINT numHalfVertices = ARRAYSIZE(HalfVertices);

		static const Vertex BothVertices[] =
		{
			// 正面
			{ Float3(-width, -width, 0.0f), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(-width, +width, 0.0f), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+width, +width, 0.0f), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+width, -width, 0.0f), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },

			// 背面
			{ Float3(-width, +width, 0.0f), Float2(0.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(-width, -width, 0.0f), Float2(0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+width, -width, 0.0f), Float2(1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f) },
			{ Float3(+width, +width, 0.0f), Float2(1.0f, 1.0f), Float3(0.0f, 0.0f, -1.0f) },
		};

		static UINT numBothVertices = ARRAYSIZE(BothVertices);

		static const unsigned short indices[] =
		{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
		};

		UINT numIndices = ARRAYSIZE(indices);

		auto polygon = std::make_shared<Polygon>();

		polygon->Initialize(
			isBoth ? BothVertices : HalfVertices,
			isBoth ? numBothVertices : numHalfVertices,
			indices,
			numIndices,
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		return polygon;
	}

	void Polygon::Render()
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

	/// <summary>初期化</summary>
	/// <param name="vertices">頂点配列</param>
	/// <param name="numVertices">頂点数</param>
	/// <param name="indices">添字配列</param>
	/// <param name="numIndices">添字数</param>
	/// <param name="topology">プリミティブ型</param>
	void Polygon::Initialize(
		const Vertex* vertices,
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
		bufferDesc.ByteWidth = sizeof(Vertex) * numVertices;
		initData.pSysMem = vertices;

		auto device = Window::Device();

		device->CreateBuffer(
			&bufferDesc, &initData, &m_vertexBuffer);

		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.ByteWidth = sizeof(WORD) * numIndices;
		initData.pSysMem = indices;

		device->CreateBuffer(
			&bufferDesc, &initData, &m_indexBuffer);

		m_stride = sizeof(Vertex);

		m_offset = 0U;

		m_numIndices = numIndices;

		m_topology = topology;
	}
}
