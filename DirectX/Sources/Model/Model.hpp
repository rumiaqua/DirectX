# pragma once

# include "Polygon/Polygon.hpp"

namespace aqua
{
	class Model : public Polygon
	{
	public:

		Model(const String& filename);

		void Load(const String& filename);
		
		virtual ~Model();
	};
}
