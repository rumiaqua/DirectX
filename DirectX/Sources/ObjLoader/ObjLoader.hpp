# pragma once

# include <string>

# include <vector>

# include "Vertex/Vertex.hpp"

/// <summary>OBJファイル読込クラス</summary>
class ObjLoader
{
private:

	/// <summary>面情報クラス</summary>
	struct FaceElement
	{
		WORD vertexIndex;

		WORD texcoordIndex;

		WORD normalIndex;

		FaceElement(WORD w, WORD t, WORD n)
			: vertexIndex(w)
			, texcoordIndex(t)
			, normalIndex(n)
		{

		}
		/// <summary>比較演算子オーバーロード</summary>
		/// <remarks>コンテナのfindを行なうために必要</remarks>
		bool operator == (const FaceElement& other)
		{
			return
				vertexIndex == other.vertexIndex &&
				texcoordIndex == other.texcoordIndex &&
				normalIndex == other.normalIndex;
		}
	};

public:

	/// <summary>コンストラクタ</summary>
	ObjLoader();

	/// <summary>コンストラクタ</summary>
	/// <param name="filename">ファイル名</param>
	ObjLoader(const String& filename);

public:

	/// <summary>OBJファイル読込</summary>
	/// <param name="filename">ファイル名</param>
	void Load(const String& filename);

	/// <summary>頂点リストを返す</summary>
	/// <returns>頂点リスト</returns>
	std::vector<Vertex> Vertices() const;

	/// <summary>インデックスリストを返す</summary>
	/// <remarks>インデックスリスト</returns>
	std::vector<WORD> Indices() const;

	/// <summary>プリミティブの型を返す</summary>
	/// <returns>プリミティブ型</returns>
	D3D11_PRIMITIVE_TOPOLOGY Topology() const;

private:

	/// <summary>座標データをバッファに追加</summary>
	/// <param name="x">x座標の文字列</param>
	/// <param name="y">y座標の文字列</param>
	/// <param name="z">z座標の文字列</param>
	void Position(const String& x, const String& y, const String& z);

	/// <summary>法線データをバッファに追加</summary>
	/// <param name="x">x座標の文字列</param>
	/// <param name="y">y座標の文字列</param>
	/// <param name="z">z座標の文字列</param>
	void Normal(const String& x, const String& y, const String& z);

	/// <summary>テクスチャ座標データをバッファに追加</summary>
	/// <param name="x">u座標の文字列</param>
	/// <param name="y">v座標の文字列</param>
	void Texcoord(const String& u, const String& v);

	/// <summary>面データをバッファに追加</summary>
	/// <param name="f1">1つ目の面の文字列</param>
	/// <param name="f2">2つ目の面の文字列</param>
	/// <param name="f3">3つ目の面の文字列</param>
	void Face(const String& f1, const String& f2, const String& f3);

	/// <summary>面データをバッファに追加</summary>
	/// <param name="f">面データ</param>
	void Face(const String& f);

private:

	/// <summary>頂点バッファ</summary>
	std::vector<Vector3> m_positions;

	/// <summary>法線バッファ</summary>
	std::vector<Vector3> m_normals;

	/// <summary>テクスチャ座標バッファ</summary>
	std::vector<Vector2> m_texcoords;

	/// <summary>面バッファ</summary>
	std::vector<FaceElement> m_faces;

	/// <summary>頂点リスト</summary>
	std::vector<Vertex> m_vertices;

	/// <summary>インデックスリスト</summary>
	std::vector<WORD> m_indices;

	/// <summary>プリミティブ型</summary>
	D3D11_PRIMITIVE_TOPOLOGY m_topology;
};
