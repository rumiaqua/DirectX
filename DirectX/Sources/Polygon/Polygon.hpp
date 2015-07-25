/// 頂点とインデックスデータを保持して描画を行なうクラス

# pragma once

# include "Handle/Handle.hpp"

# include <memory>

class Vertex;

namespace aqua
{
	/// <summary>ポリゴンクラス</summary>
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

		/// <summary>初期化</summary>
		/// <param name="vertices">頂点配列</param>
		/// <param name="numVertices">頂点数</param>
		/// <param name="indices">添字配列</param>
		/// <param name="numIndices">添字数</param>
		/// <param name="topology">プリミティブ型</param>
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
