# pragma once

# include "Polygon/Polygon.hpp"

# include "ObjLoader/ObjLoader.hpp"

# include <fstream>

namespace aqua
{
	class Model : public Polygon
	{
	public:

		Model(const std::wstring& filename)
		{
			Load(filename);
		}

		void Load(const std::wstring& filename)
		{
			HRESULT hr = S_OK;

			ObjLoader loader { filename };

			auto vertices = loader.Vertices();

			auto indices = loader.Indices();

			Initialize(
				vertices.data(),
				vertices.size(),
				indices.data(),
				indices.size(),
				loader.Topology());
		}

		virtual ~Model()
		{

		}
	};
}
