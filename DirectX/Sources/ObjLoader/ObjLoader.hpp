# pragma once

# include <string>

# include <vector>

# include "Primitive/Primitive.hpp"

# include "SimpleVertex/SimpleVertex.hpp"

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
	ObjLoader(const std::wstring& filename);

public:

	/// <summary>OBJ�t�@�C���Ǎ�</summary>
	/// <param name="filename">�t�@�C����</param>
	void Load(const std::wstring& filename);

	/// <summary>���_���X�g��Ԃ�</summary>
	/// <returns>���_���X�g</returns>
	std::vector<SimpleVertex> Vertices() const;

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
	void Position(const std::wstring& x, const std::wstring& y, const std::wstring& z);

	/// <summary>�@���f�[�^���o�b�t�@�ɒǉ�</summary>
	/// <param name="x">x���W�̕�����</param>
	/// <param name="y">y���W�̕�����</param>
	/// <param name="z">z���W�̕�����</param>
	void Normal(const std::wstring& x, const std::wstring& y, const std::wstring& z);

	/// <summary>�e�N�X�`�����W�f�[�^���o�b�t�@�ɒǉ�</summary>
	/// <param name="x">u���W�̕�����</param>
	/// <param name="y">v���W�̕�����</param>
	void Texcoord(const std::wstring& u, const std::wstring& v);

	/// <summary>�ʃf�[�^���o�b�t�@�ɒǉ�</summary>
	/// <param name="f1">1�ڂ̖ʂ̕�����</param>
	/// <param name="f2">2�ڂ̖ʂ̕�����</param>
	/// <param name="f3">3�ڂ̖ʂ̕�����</param>
	void Face(const std::wstring& f1, const std::wstring& f2, const std::wstring& f3);

	/// <summary>�ʃf�[�^���o�b�t�@�ɒǉ�</summary>
	/// <param name="f">�ʃf�[�^</param>
	void Face(const std::wstring& f);

private:

	/// <summary>���_�o�b�t�@</summary>
	std::vector<Float3> m_positions;

	/// <summary>�@���o�b�t�@</summary>
	std::vector<Float3> m_normals;

	/// <summary>�e�N�X�`�����W�o�b�t�@</summary>
	std::vector<Float2> m_texcoords;

	/// <summary>�ʃo�b�t�@</summary>
	std::vector<FaceElement> m_faces;

	/// <summary>���_���X�g</summary>
	std::vector<SimpleVertex> m_vertices;

	/// <summary>�C���f�b�N�X���X�g</summary>
	std::vector<WORD> m_indices;

	/// <summary>�v���~�e�B�u�^</summary>
	D3D11_PRIMITIVE_TOPOLOGY m_topology;
};
