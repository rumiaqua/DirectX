# pragma once

# include "Polygon/Polygon.hpp"

namespace aqua
{
	class Texture2D : public Polygon
	{
	public:

		Texture2D(const std::wstring& filename);

		void Load(const std::wstring& filename);

		virtual ~Texture2D();

		void Render() override;

	private:

		Handle<ID3D11ShaderResourceView> m_shaderResource;
	};
}
