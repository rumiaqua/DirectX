# include "ObjLoader.hpp"

# include <fstream>

# include <vector>

# include <sstream>

# include <algorithm>

# include "Convert/Convert.hpp"

/// <summary>文字列を指定の文字で分割する</summary>
/// <param name="str">文字列</param>
/// <param name="delim">分割点の文字</param>
/// <returns>分割した文字列の入ったコンテナ</returns>
std::vector<std::wstring> Split(const std::wstring& str, char delim)
{
	std::vector<std::wstring> res;
	UINT current = 0, found;

	while ((found = str.find_first_of(delim, current)) != std::wstring::npos)
	{
		res.push_back(std::wstring(str, current, found - current));
		current = found + 1;
	}
	res.push_back(std::wstring(str, current, str.size() - current));
	return res;
}

ObjLoader::ObjLoader()
	: m_positions()
	, m_faces()
	, m_vertices()
	, m_indices()
{

}

ObjLoader::ObjLoader(const std::wstring& filename)
	: ObjLoader()
{
	Load(filename);
}

void ObjLoader::Load(const std::wstring& filename)
{
	std::wifstream ifs { filename };

	std::wstring buffer;

	// 最後まで読む
	while (std::getline(ifs, buffer))
	{
		// 半角スペースで分割
		auto split = Split(buffer, ' ');

		// 最初の文字で判断
		switch (buffer[0])
		{
			case 'v':
			{
				// ２文字目で判断
				switch (buffer[1])
				{
					case 'n':
					Normal(split[1], split[2], split[3]);
					break;

					case 't':
					Texcoord(split[1], split[2]);
					break;

					default:
					Position(split[1], split[2], split[3]);
					break;
				}
			}
			break;

			case 'f':
			{
				Face(split[1], split[2], split[3]);
				// 今は三面データのみを扱う
				m_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			}
			break;
		}
	}

	std::vector<FaceElement> temp;

	// 面データから実際の面リストを作成
	for (const auto& f : m_faces)
	{
		static UINT id = 0;
		auto it = std::find(temp.begin(), temp.end(), f);
		if (it == temp.end())
		{
			temp.emplace_back(f);
			m_indices.emplace_back(id++);
			continue;
		}
		UINT index = it - temp.begin();
		m_indices.emplace_back(index);
	}

	// 頂点リストを作成
	for (const auto& f : temp)
	{
		m_vertices.emplace_back(
			m_positions[f.vertexIndex - 1],
			f.texcoordIndex == 0 ? Float2(0.0f, 0.0f) : m_texcoords[f.texcoordIndex - 1],
			f.normalIndex == 0 ? m_positions[f.vertexIndex - 1] : m_normals[f.normalIndex - 1]);
	}
}

std::vector<SimpleVertex> ObjLoader::Vertices() const
{
	return m_vertices;
}

std::vector<WORD> ObjLoader::Indices() const
{
	return m_indices;
}

D3D11_PRIMITIVE_TOPOLOGY ObjLoader::Topology() const
{
	return m_topology;
}

void ObjLoader::Position(const std::wstring& x, const std::wstring& y, const std::wstring& z)
{
	m_positions.emplace_back(
		// ToValue<float>(x), ToValue<float>(y), ToValue<float>(z));
		ToValue<float>(x), ToValue<float>(y), ToValue<float>(z));
}

void ObjLoader::Normal(const std::wstring& x, const std::wstring& y, const std::wstring& z)
{
	m_normals.emplace_back(
		ToValue<float>(x), ToValue<float>(y), ToValue<float>(z));
}

void ObjLoader::Texcoord(const std::wstring& u, const std::wstring& v)
{
	m_texcoords.emplace_back(
		ToValue<float>(u), ToValue<float>(v));
}

void ObjLoader::Face(const std::wstring& f1, const std::wstring& f2, const std::wstring& f3)
{
	Face(f1);
	Face(f2);
	Face(f3);
}

void ObjLoader::Face(const std::wstring& f)
{
	// スラッシュで分割
	auto split = Split(f, '/');

	// 要素数で判断
	switch (split.size())
	{
		// 1つなら座標のみ
		case 1:
		{
			m_faces.emplace_back(ToValue<WORD>(split[0]), 0, 0);
			break;
		}
		// 2つなら座標とUV座標
		case 2:
		{
			m_faces.emplace_back(ToValue<WORD>(split[0]), ToValue<WORD>(split[1]), 0);
			break;
		}
		// 3つなら座標と（UV座標と）法線
		case 3:
		{
			m_faces.emplace_back(ToValue<WORD>(split[0]), split[1].size() > 1 ? ToValue<WORD>(split[1]) : 0U, ToValue<WORD>(split[2]));
			break;
		}
	}
}
