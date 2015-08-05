# include "Texture2D.hpp"

# include "Convert/Convert.hpp"

# include "Shader/Shader.hpp"

# include "Window/Window.hpp"

namespace aqua
{
	Texture2D::Texture2D(const String& filename)
	{
		Load(filename);
	}

	void Texture2D::Load(const String& filename)
	{
		DirectX::TexMetadata metadata;
		DirectX::ScratchImage image;

		HRESULT hr = S_OK;

		auto split = filename.Split(L'.');

		if (split.back() == L"tga")
		{
			hr = DirectX::LoadFromTGAFile(
				filename,
				&metadata,
				image);
		}
		else if (split.back() == L"dds")
		{
			hr = DirectX::LoadFromDDSFile(
				filename,
				0U,
				&metadata,
				image);
		}
		else
		{
			hr = DirectX::LoadFromWICFile(
				filename,
				0U,
				&metadata,
				image);
		}

		if (FAILED(hr))
		{
			throw std::exception("テクスチャの読込に失敗しました");
		}

		hr = DirectX::CreateShaderResourceView(
			Window::Device(),
			image.GetImages(),
			image.GetImageCount(),
			metadata,
			&m_shaderResource);

		if (FAILED(hr))
		{
			throw std::exception("リソースの生成に失敗しました");
		}

		m_width = (float)metadata.width;
		m_height = (float)metadata.height;

		static const Vertex vertices[] =
		{
			// 正面
			{ Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f) },
			{ Vector3(1.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f) },
			{ Vector3(0.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f) },
			{ Vector3(1.0f, 1.0f, 0.0f), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f) },
		};

		UINT numVertices = ARRAYSIZE(vertices);

		static const unsigned short indices[] =
		{
			0, 1, 2, 3,
		};

		UINT numIndices = ARRAYSIZE(indices);

		Initialize(
			vertices,
			numVertices,
			indices,
			numIndices,
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}

	Texture2D::~Texture2D()
	{

	}

	void Texture2D::Render()
	{
		static const Matrix Projection =
		{
			2.0f / Window::Width(), 0.0f, 0.0f, 0.0f,
			0.0f, -2.0f / Window::Height(), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f, 1.0f
		};

		Shader::SetMatrix(L"projection", Projection);
		Shader::SetShaderResource(L"texture2d", m_shaderResource);
		Shader::SetMatrix(L"world", DirectX::XMMatrixScaling(m_width, m_height, 1.0f));
		Shader::SetVector(L"color", { 1.0f, 1.0f, 1.0f, 1.0f });

		Polygon::Render();
	}
}
