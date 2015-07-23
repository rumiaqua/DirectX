# pragma once

# include "Polygon/Polygon.hpp"

namespace aqua
{
	class Model : public Polygon
	{
	public:

		Model(const std::wstring& filename);

		void Load(const std::wstring& filename);
		
		virtual ~Model();
	};
}
