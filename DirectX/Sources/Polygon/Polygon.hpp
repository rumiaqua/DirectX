/// ���_�ƃC���f�b�N�X�f�[�^��ێ����ĕ`����s�Ȃ��N���X

# pragma once

# include "Handle/Handle.hpp"

# include <memory>

class Vertex;

namespace aqua
{
	/// <summary>�|���S���N���X</summary>
	class Polygon
	{
	public:

		Polygon();

		virtual ~Polygon();

		static std::shared_ptr<Polygon> Box();

		static std::shared_ptr<Polygon> Plane();

		virtual void Render();

	private:

		virtual void OnRender();

	protected:

		/// <summary>������</summary>
		/// <param name="vertices">���_�z��</param>
		/// <param name="numVertices">���_��</param>
		/// <param name="indices">�Y���z��</param>
		/// <param name="numIndices">�Y����</param>
		/// <param name="topology">�v���~�e�B�u�^</param>
		void Initialize(
			const Vertex* vertices,
			UINT numVertices,
			const WORD* indices,
			UINT numIndices,
			D3D11_PRIMITIVE_TOPOLOGY topology);

	private:

		Handle<ID3D11Buffer> m_vertexBuffer;

		UINT m_stride;

		UINT m_offset;

		Handle<ID3D11Buffer> m_indexBuffer;

		UINT m_numIndices;

		D3D11_PRIMITIVE_TOPOLOGY m_topology;
	};
}
