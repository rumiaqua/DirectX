# include "Model.hpp"

# include "ObjLoader/ObjLoader.hpp"

# include "Experimental/TestLoader/TestLoader.hpp"

namespace aqua
{

	Model::Model(const std::wstring& filename)
	{
		Load(filename);
	}

	void Model::Load(const std::wstring& filename)
	{
		HRESULT hr = S_OK;

		Experimental::TestLoader loader { L"Contents/Box.obj" };
		auto vertices = loader.Vertices();
		auto indices = loader.Indices();

		/*ObjLoader loader { filename };

		auto vertices = loader.Vertices();

		auto indices = loader.Indices();*/

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
