# pragma once

using namespace aqua;

/// <summary>頂点データ</summary>
struct Vertex
{
	Vector3 position;
	Vector2 texcoord;
	Vector3 normal;
	Vertex()
		: Vertex(Vector3(), Vector2(), Vector3())
	{

	}
	Vertex(const Vector3& position, const Vector2& texcoord, const Vector3& normal)
		: position(position)
		, texcoord(texcoord)
		, normal(normal)
	{

	}
};
