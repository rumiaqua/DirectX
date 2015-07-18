# pragma once

# include "Primitive/Primitive.hpp"

/// <summary>頂点データ</summary>
struct SimpleVertex
{
	Float3 position;
	Float2 texcoord;
	Float3 normal;
	SimpleVertex()
		: SimpleVertex(Float3(), Float2(), Float3())
	{

	}
	SimpleVertex(const Float3& position, const Float2& texcoord, const Float3& normal)
		: position(position)
		, texcoord(texcoord)
		, normal(normal)
	{

	}
};
