# pragma once

# include <string>

# include <vector>

# include "Primitive/Primitive.hpp"

# include "SimpleVertex/SimpleVertex.hpp"

class ObjLoader
{
private:

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
		bool operator == (const FaceElement& other)
		{
			return
				vertexIndex == other.vertexIndex &&
				texcoordIndex == other.texcoordIndex &&
				normalIndex == other.normalIndex;
		}
	};

public:

	ObjLoader();

	ObjLoader(const std::wstring& filename);

public:

	void Load(const std::wstring& filename);

	std::vector<SimpleVertex> Vertices() const;

	std::vector<WORD> Indices() const;

	D3D11_PRIMITIVE_TOPOLOGY Topology() const;

private:

	void Position(const std::wstring& x, const std::wstring& y, const std::wstring& z);

	void Normal(const std::wstring& x, const std::wstring& y, const std::wstring& z);

	void Texcoord(const std::wstring& u, const std::wstring& v);

	void Face(const std::wstring& f1, const std::wstring& f2, const std::wstring& f3);

	void Face(const std::wstring& f);

private:

	// 座標リスト
	std::vector<Float3> m_positions;

	std::vector<Float3> m_normals;

	std::vector<Float2> m_texcoords;

	// 面リスト(インデックス保持)
	std::vector<FaceElement> m_faces;

	// 頂点リスト
	std::vector<SimpleVertex> m_vertices;

	// インデックスリスト
	std::vector<WORD> m_indices;

	D3D11_PRIMITIVE_TOPOLOGY m_topology;
};
