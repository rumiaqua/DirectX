# include "ObjLoader.hpp"

# include <fstream>

# include <vector>

# include <algorithm>

# include "Convert/Convert.hpp"

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

	// �Ō�܂œǂ�
	while (std::getline(ifs, buffer))
	{
		// ���p�X�y�[�X�ŕ���
		auto split = Split(buffer, ' ');

		// �ŏ��̕����Ŕ��f
		switch (buffer[0])
		{
			case 'v':
			{
				// �Q�����ڂŔ��f
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
				switch (split.size())
				{
					case 4:
					{
						Face(split[1], split[2], split[3]);
						m_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
					}
					break;

					case 5:
					{
						Face(split[1]);
						Face(split[2]);
						Face(split[3]);
						Face(split[3]);
						Face(split[4]);
						Face(split[1]);
						m_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
					}
				}
			}
			break;
		}
	}

	std::vector<FaceElement> temp;

	// �ʃf�[�^������ۂ̖ʃ��X�g���쐬
	UINT id = 0;
	for (const auto& f : m_faces)
	{
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

	// ���_���X�g���쐬
	for (const auto& f : temp)
	{
		m_vertices.emplace_back(
			m_positions[f.vertexIndex - 1],
			f.texcoordIndex == 0 ? Float2(0.0f, 0.0f) : m_texcoords[f.texcoordIndex - 1],
			f.normalIndex == 0 ? m_positions[f.vertexIndex - 1] : m_normals[f.normalIndex - 1]);
	}
}

std::vector<Vertex> ObjLoader::Vertices() const
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
	// �X���b�V���ŕ���
	auto split = Split(f, '/');

	// �v�f���Ŕ��f
	switch (split.size())
	{
		// 1�Ȃ���W�̂�
		case 1:
		{
			m_faces.emplace_back(ToValue<WORD>(split[0]), 0, 0);
			break;
		}
		// 2�Ȃ���W��UV���W
		case 2:
		{
			m_faces.emplace_back(ToValue<WORD>(split[0]), ToValue<WORD>(split[1]), 0);
			break;
		}
		// 3�Ȃ���W�ƁiUV���W�Ɓj�@��
		case 3:
		{
			m_faces.emplace_back(ToValue<WORD>(split[0]), split[1].size() > 1 ? ToValue<WORD>(split[1]) : 0U, ToValue<WORD>(split[2]));
			break;
		}
	}
}
