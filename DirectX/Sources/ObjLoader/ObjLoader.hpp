# pragma once

# include <string>

# include <vector>

# include "Vertex/Vertex.hpp"

/// <summary>OBJ�t�@�C���Ǎ��N���X</summary>
class ObjLoader
{
private:

	/// <summary>�ʏ��N���X</summary>
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
		/// <summary>��r���Z�q�I�[�o�[���[�h</summary>
		/// <remarks>�R���e�i��find���s�Ȃ����߂ɕK�v</remarks>
		bool operator == (const FaceElement& other)
		{
			return
				vertexIndex == other.vertexIndex &&
				texcoordIndex == other.texcoordIndex &&
				normalIndex == other.normalIndex;
		}
	};

public:

	/// <summary>�R���X�g���N�^</summary>
	ObjLoader();

	/// <summary>�R���X�g���N�^</summary>
	/// <param name="filename">�t�@�C����</param>
	ObjLoader(const String& filename);

public:

	/// <summary>OBJ�t�@�C���Ǎ�</summary>
	/// <param name="filename">�t�@�C����</param>
	void Load(const String& filename);

	/// <summary>���_���X�g��Ԃ�</summary>
	/// <returns>���_���X�g</returns>
	std::vector<Vertex> Vertices() const;

	/// <summary>�C���f�b�N�X���X�g��Ԃ�</summary>
	/// <remarks>�C���f�b�N�X���X�g</returns>
	std::vector<WORD> Indices() const;

	/// <summary>�v���~�e�B�u�̌^��Ԃ�</summary>
	/// <returns>�v���~�e�B�u�^</returns>
	D3D11_PRIMITIVE_TOPOLOGY Topology() const;

private:

	/// <summary>���W�f�[�^���o�b�t�@�ɒǉ�</summary>
	/// <param name="x">x���W�̕�����</param>
	/// <param name="y">y���W�̕�����</param>
	/// <param name="z">z���W�̕�����</param>
	void Position(const String& x, const String& y, const String& z);

	/// <summary>�@���f�[�^���o�b�t�@�ɒǉ�</summary>
	/// <param name="x">x���W�̕�����</param>
	/// <param name="y">y���W�̕�����</param>
	/// <param name="z">z���W�̕�����</param>
	void Normal(const String& x, const String& y, const String& z);

	/// <summary>�e�N�X�`�����W�f�[�^���o�b�t�@�ɒǉ�</summary>
	/// <param name="x">u���W�̕�����</param>
	/// <param name="y">v���W�̕�����</param>
	void Texcoord(const String& u, const String& v);

	/// <summary>�ʃf�[�^���o�b�t�@�ɒǉ�</summary>
	/// <param name="f1">1�ڂ̖ʂ̕�����</param>
	/// <param name="f2">2�ڂ̖ʂ̕�����</param>
	/// <param name="f3">3�ڂ̖ʂ̕�����</param>
	void Face(const String& f1, const String& f2, const String& f3);

	/// <summary>�ʃf�[�^���o�b�t�@�ɒǉ�</summary>
	/// <param name="f">�ʃf�[�^</param>
	void Face(const String& f);

private:

	/// <summary>���_�o�b�t�@</summary>
	std::vector<Vector3> m_positions;

	/// <summary>�@���o�b�t�@</summary>
	std::vector<Vector3> m_normals;

	/// <summary>�e�N�X�`�����W�o�b�t�@</summary>
	std::vector<Vector2> m_texcoords;

	/// <summary>�ʃo�b�t�@</summary>
	std::vector<FaceElement> m_faces;

	/// <summary>���_���X�g</summary>
	std::vector<Vertex> m_vertices;

	/// <summary>�C���f�b�N�X���X�g</summary>
	std::vector<WORD> m_indices;

	/// <summary>�v���~�e�B�u�^</summary>
	D3D11_PRIMITIVE_TOPOLOGY m_topology;
};
