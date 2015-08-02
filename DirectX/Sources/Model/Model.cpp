# include "Model.hpp"

# include "ObjLoader/ObjLoader.hpp"

namespace aqua
{

	Model::Model(const String& filename)
	{
		Load(filename);
	}

	void Model::Load(const String& filename)
	{
		HRESULT hr = S_OK;

		/*Experimental::TestLoader loader { L"Contents/Box.obj" };
		auto vertices = loader.Vertices();
		auto indices = loader.Indices();*/

		ObjLoader loader { filename };

		auto vertices = loader.Vertices();

		auto indices = loader.Indices();

		Initialize(
			vertices.data(),
			vertices.size(),
			indices.data(),
			indices.size(),
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	Model::~Model()
	{

	}
}
