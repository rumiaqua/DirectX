# pragma once

# include "Polygon/Polygon.hpp"

namespace aqua
{
	class Texture2D : public Polygon
	{
	public:

		Texture2D(const String& filename);

		void Load(const String& filename);

		virtual ~Texture2D();

		void Render() override;

	private:

		Handle<ID3D11ShaderResourceView> m_shaderResource;

		float m_width;

		float m_height;
	};
}
