# include "TestLoader.hpp"

# include <fstream>

# include <string>

# include "Convert/Convert.hpp"

# include "Vector3/Vector3.hpp"

namespace Experimental
{
	struct VertexIndex
	{
		WORD positionIndex;

		WORD texcoordIndex;
	};

	struct Face
	{
		VertexIndex p0;

		VertexIndex p1;

		VertexIndex p2;

		WORD normalIndex;
	};

	TestLoader::TestLoader(const std::wstring& filepath)
	{
		std::wifstream ifs { filepath };

		std::wstring buffer;

		std::vector<Float3> positionBuffer;

		std::vector<Float2> texcoordBuffer;

		std::vector<Float3> normalBuffer;

		std::vector<Face> faceBuffer;

		while (std::getline(ifs, buffer))
		{
			// 半角スペースで区切る
			auto split = Split(buffer, ' ');

			// 1文字目で判断
			switch (buffer[0])
			{
				// vなら更に派生
				// バッファの構築
				case L'v':
				{
					// 2文字目で判断
					switch (buffer[1])
					{
						// 法線
						case L'n':
						{
							normalBuffer.emplace_back(
								ToValue<float>(split[1]),
								ToValue<float>(split[2]),
								ToValue<float>(split[3]));
						}
						break;

						// UV
						case L't':
						{
							texcoordBuffer.emplace_back(
								ToValue<float>(split[1]),
								ToValue<float>(split[2]));
						}
						break;

						// 座標
						default:
						{
							positionBuffer.emplace_back(
								ToValue<float>(split[1]),
								ToValue<float>(split[2]),
								ToValue<float>(split[3]));
						}
						break;
					}
				}
				break;

				// 面データ
				// 分割して読み込む
				case L'f':
				{
					// p0の処理
					// 分割
					auto elm = Split(split[1], '/');
					VertexIndex p0;
					// 頂点は必ずあるのでそのまま取得
					p0.positionIndex = ToValue<WORD>(elm[0]);
					// サイズが2の時
					// またはサイズが3で空白でない時
					// UVを取得
					// そうでない場合無効値として0を入れる
					p0.texcoordIndex =
						elm.size() == 2 || elm.size() == 3 && elm[2] != L""
						? ToValue<WORD>(elm[1]) : 0;

					// p1の処理
					// 分割
					elm = Split(split[2], '/');
					VertexIndex p1;
					// 頂点は必ずあるのでそのまま取得
					p1.positionIndex = ToValue<WORD>(elm[0]);
					// サイズが2の時
					// またはサイズが3で空白でない時
					// UVを取得
					// そうでない場合無効値として0を入れる
					p1.texcoordIndex =
						elm.size() == 2 || elm.size() == 3 && elm[2] != L""
						? ToValue<WORD>(elm[1]) : 0;

					// p2の処理
					// 分割
					elm = Split(split[3], '/');
					VertexIndex p2;
					// 頂点は必ずあるのでそのまま取得
					p2.positionIndex = ToValue<WORD>(elm[0]);
					// サイズが2の時
					// またはサイズが3で空白でない時
					// UVを取得
					// そうでない場合無効値として0を入れる
					p2.texcoordIndex =
						elm.size() == 2 || elm.size() == 3 && elm[2] != L""
						? ToValue<WORD>(elm[1]) : 0;

					WORD normalIndex;

					// 法線の計算
					if (elm.size() != 3)
					{
						Vector3 v0 = positionBuffer[p0.positionIndex - 1];
						Vector3 v1 = positionBuffer[p1.positionIndex - 1];
						Vector3 v2 = positionBuffer[p2.positionIndex - 1];

						auto normal =
								Vector3::Cross(v1 - v0, v2 - v0);
						normal = Vector3::Normalize(normal);
						normalIndex = normalBuffer.size();
						normalBuffer.emplace_back(normal);
					}
					else
					{
						normalIndex = ToValue<WORD>(elm[3]);
					}

					Face face;
					face.p0 = p0;
					face.p1 = p1;
					face.p2 = p2;
					face.normalIndex = normalIndex;
					faceBuffer.push_back(face);
				}
				break;
			}
		}

		// ここまでで読み込み完了

		// 頂点法線の計算
		std::vector<Float3> vertexNormalBuffer;

		auto normalAddBlend = [&] (UINT verticesIndex, UINT normalIndex)
		{
			auto normal = normalBuffer[normalIndex];

			// 頂点法線リストに存在しなければ追加
			if (vertexNormalBuffer.size() <= verticesIndex)
			{
				vertexNormalBuffer.push_back(normal);
				return;
			}

			// そうでなければ合成
			vertexNormalBuffer[verticesIndex] =
				Vector3::Normalize(
					vertexNormalBuffer[verticesIndex] + normal);
		};

		for (auto&& face : faceBuffer)
		{
			normalAddBlend(face.p0.positionIndex, face.normalIndex);
			normalAddBlend(face.p1.positionIndex, face.normalIndex);
			normalAddBlend(face.p2.positionIndex, face.normalIndex);
		}

		// 頂点リストの生成
		for (auto&& face : faceBuffer)
		{
			m_vertices.emplace_back(
				positionBuffer[face.p0.positionIndex - 1],
				texcoordBuffer[face.p0.texcoordIndex - 1],
				vertexNormalBuffer[face.p0.positionIndex]);
			m_vertices.emplace_back(
				positionBuffer[face.p1.positionIndex - 1],
				texcoordBuffer[face.p1.texcoordIndex - 1],
				vertexNormalBuffer[face.p1.positionIndex]);
			m_vertices.emplace_back(
				positionBuffer[face.p2.positionIndex - 1],
				texcoordBuffer[face.p2.texcoordIndex - 1],
				vertexNormalBuffer[face.p2.positionIndex]);

			m_indices.emplace_back(face.p0.positionIndex - 1);
			m_indices.emplace_back(face.p1.positionIndex - 1);
			m_indices.emplace_back(face.p2.positionIndex - 1);
		}
		m_indices.clear();

		m_vertices.size();
		for (WORD i = 0; i < m_vertices.size(); ++i)
		{
			m_indices.push_back(i);
		}

		m_vertices.clear();
		m_indices.clear();

		m_vertices.emplace_back(Float3(+1.0f, -1.0f, -1.0f), Float2(1.0f, 1.0f), Float3(+1.0f, -1.0f, -1.0f));
		m_vertices.emplace_back(Float3(-1.0f, -1.0f, -1.0f), Float2(0.0f, 1.0f), Float3(-1.0f, -1.0f, -1.0f));
		m_vertices.emplace_back(Float3(-1.0f, +1.0f, -1.0f), Float2(0.0f, 0.0f), Float3(-1.0f, +1.0f, -1.0f));
		m_vertices.emplace_back(Float3(+1.0f, +1.0f, -1.0f), Float2(1.0f, 0.0f), Float3(+1.0f, +1.0f, -1.0f));

		m_vertices.emplace_back(Float3(-1.0f, -1.0f, +1.0f), Float2(1.0f, 1.0f), Float3(-1.0f, -1.0f, +1.0f));
		m_vertices.emplace_back(Float3(+1.0f, -1.0f, +1.0f), Float2(0.0f, 1.0f), Float3(+1.0f, -1.0f, +1.0f));
		m_vertices.emplace_back(Float3(+1.0f, +1.0f, +1.0f), Float2(0.0f, 0.0f), Float3(+1.0f, +1.0f, +1.0f));
		m_vertices.emplace_back(Float3(-1.0f, +1.0f, +1.0f), Float2(1.0f, 0.0f), Float3(-1.0f, +1.0f, +1.0f));

		m_vertices.emplace_back(Float3(-1.0f, -1.0f, -1.0f), Float2(1.0f, 1.0f), Float3(-1.0f, -1.0f, -1.0f));
		m_vertices.emplace_back(Float3(-1.0f, -1.0f, +1.0f), Float2(0.0f, 1.0f), Float3(-1.0f, -1.0f, +1.0f));
		m_vertices.emplace_back(Float3(-1.0f, +1.0f, +1.0f), Float2(0.0f, 0.0f), Float3(-1.0f, +1.0f, +1.0f));
		m_vertices.emplace_back(Float3(-1.0f, +1.0f, -1.0f), Float2(1.0f, 0.0f), Float3(-1.0f, +1.0f, -1.0f));

		m_vertices.emplace_back(Float3(+1.0f, -1.0f, +1.0f), Float2(1.0f, 1.0f), Float3(+1.0f, -1.0f, +1.0f));
		m_vertices.emplace_back(Float3(+1.0f, -1.0f, -1.0f), Float2(0.0f, 1.0f), Float3(+1.0f, -1.0f, -1.0f));
		m_vertices.emplace_back(Float3(+1.0f, +1.0f, -1.0f), Float2(0.0f, 0.0f), Float3(+1.0f, +1.0f, -1.0f));
		m_vertices.emplace_back(Float3(+1.0f, +1.0f, +1.0f), Float2(1.0f, 0.0f), Float3(+1.0f, +1.0f, +1.0f));

		m_vertices.emplace_back(Float3(+1.0f, +1.0f, -1.0f), Float2(1.0f, 1.0f), Float3(+1.0f, +1.0f, -1.0f));
		m_vertices.emplace_back(Float3(-1.0f, +1.0f, -1.0f), Float2(0.0f, 1.0f), Float3(-1.0f, +1.0f, -1.0f));
		m_vertices.emplace_back(Float3(-1.0f, +1.0f, +1.0f), Float2(0.0f, 0.0f), Float3(-1.0f, +1.0f, +1.0f));
		m_vertices.emplace_back(Float3(+1.0f, +1.0f, +1.0f), Float2(1.0f, 0.0f), Float3(+1.0f, +1.0f, +1.0f));

		m_vertices.emplace_back(Float3(+1.0f, -1.0f, +1.0f), Float2(1.0f, 1.0f), Float3(+1.0f, -1.0f, +1.0f));
		m_vertices.emplace_back(Float3(-1.0f, -1.0f, +1.0f), Float2(0.0f, 1.0f), Float3(-1.0f, -1.0f, +1.0f));
		m_vertices.emplace_back(Float3(-1.0f, -1.0f, -1.0f), Float2(0.0f, 0.0f), Float3(-1.0f, -1.0f, -1.0f));
		m_vertices.emplace_back(Float3(+1.0f, -1.0f, -1.0f), Float2(1.0f, 0.0f), Float3(+1.0f, -1.0f, -1.0f));

		m_indices.push_back(0);
		m_indices.push_back(1);
		m_indices.push_back(2);
		m_indices.push_back(2);
		m_indices.push_back(3);
		m_indices.push_back(0);

		m_indices.push_back(4);
		m_indices.push_back(5);
		m_indices.push_back(6);
		m_indices.push_back(6);
		m_indices.push_back(7);
		m_indices.push_back(4);

		m_indices.push_back(8);
		m_indices.push_back(9);
		m_indices.push_back(10);
		m_indices.push_back(10);
		m_indices.push_back(11);
		m_indices.push_back(8);

		m_indices.push_back(12);
		m_indices.push_back(13);
		m_indices.push_back(14);
		m_indices.push_back(14);
		m_indices.push_back(15);
		m_indices.push_back(12);

		m_indices.push_back(16);
		m_indices.push_back(17);
		m_indices.push_back(18);
		m_indices.push_back(18);
		m_indices.push_back(19);
		m_indices.push_back(16);

		m_indices.push_back(20);
		m_indices.push_back(21);
		m_indices.push_back(22);
		m_indices.push_back(22);
		m_indices.push_back(23);
		m_indices.push_back(20);
	}

	std::vector<Vertex> TestLoader::Vertices() const
	{
		return m_vertices;
	}

	std::vector<WORD> TestLoader::Indices() const
	{
		return m_indices;
	}
}
