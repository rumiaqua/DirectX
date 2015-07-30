# pragma once

# include "Vertex/Vertex.hpp"

# include <vector>

namespace Experimental
{
	class TestLoader
	{
	public:

		TestLoader(const std::wstring& filepath);

		std::vector<Vertex> Vertices() const;

		std::vector<WORD> Indices() const;

	private:

		std::vector<Vertex> m_vertices;

		std::vector<WORD> m_indices;
	};
}
