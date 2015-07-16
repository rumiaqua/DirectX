# pragma once

# include "Primitive/Primitive.hpp"

struct SimpleVertex
{
	Float3 position;
	Float2 texcoord;
	Float3 normal;
	SimpleVertex(const Float3& position, const Float2& texcoord, const Float3& normal)
		: position(position)
		, texcoord(texcoord)
		, normal(normal)
	{

	}
};
