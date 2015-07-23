/// ���_�ƃC���f�b�N�X�f�[�^��ێ����ĕ`����s�Ȃ��N���X

# pragma once

# include "Handle/Handle.hpp"

# include "SimpleVertex/SimpleVertex.hpp"

# include "Window/Window.hpp"

# include <memory>

namespace aqua
{
	/// <summary>�|���S���N���X</summary>
	class Polygon
	{
	public:

		Polygon()
			: m_vertexBuffer()
			, m_stride(0U)
			, m_offset(0U)
			, m_indexBuffer()
			, m_numIndices(0U)
			, m_topology()
		{

		}

		virtual ~Polygon()
		{

		}

		static std::shared_ptr<Polygon> Box()
		{
			static const SimpleVertex vertices[] =
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

		static std::shared_ptr<Polygon> Plane()
		{
			static const SimpleVertex vertices[] =
			{
				// ����
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

			auto polygon = std::make_shared<Polygon>();

			polygon->Initialize(
				vertices,
				numVertices,
				indices,
				numIndices,
				D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			return polygon;
		}

		/// <summary>�`��</summary>
		virtual void Render()
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

	protected:

		/// <summary>������</summary>
		/// <param name="vertices">���_�z��</param>
		/// <param name="numVertices">���_��</param>
		/// <param name="indices">�Y���z��</param>
		/// <param name="numIndices">�Y����</param>
		/// <param name="topology">�v���~�e�B�u�^</param>
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
	};
}
