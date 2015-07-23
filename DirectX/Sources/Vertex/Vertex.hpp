# pragma once

# include "Primitive/Primitive.hpp"

/// <summary>���_�f�[�^</summary>
struct Vertex
{
	Float3 position;
	Float2 texcoord;
	Float3 normal;
	Vertex()
		: Vertex(Float3(), Float2(), Float3())
	{

	}
	Vertex(const Float3& position, const Float2& texcoord, const Float3& normal)
		: position(position)
		, texcoord(texcoord)
		, normal(normal)
	{

	}
};
