# include "Model.hpp"

# include "ObjLoader/ObjLoader.hpp"

namespace aqua
{

	Model::Model(const std::wstring& filename)
	{
		Load(filename);
	}

	void Model::Load(const std::wstring& filename)
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

	Model::~Model()
	{

	}
}
