# pragma once

# include "IResource.hpp"

# include <unordered_map>

class Texture : public IResource
{

public:

	ID3D11ShaderResourceView* ShaderResourceView()
	{
		return m_shaderResourceView;
	}

	const ID3D11ShaderResourceView* ShaderResourceView() const
	{
		return m_shaderResourceView;
	}

private:

	virtual bool Load(const String& name) override
	{
		using namespace DirectX;

		ScratchImage image;

		String extension = name.Split(L'.').back();

		HRESULT hr = S_OK;

		if (extension == L"tga")
		{
			hr = LoadFromTGAFile(
				name,
				&m_metadata,
				image);
		}
		else if (extension == L"dds")
		{
			hr = LoadFromDDSFile(
				name,
				0U,
				&m_metadata,
				image);
		}
		else
		{
			hr = LoadFromWICFile(
				name,
				0U,
				&m_metadata,
				image);
		}

		if (FAILED(hr))
		{
			throw std::exception("テクスチャの読込に失敗しました");
		}

		hr = CreateShaderResourceView(
			Window::Device(),
			image.GetImages(),
			image.GetImageCount(),
			m_metadata,
			&m_shaderResourceView);

		if (FAILED(hr))
		{
			throw std::exception("リソースの生成に失敗しました");
		}

		return true;
	}

private:

	Handle<ID3D11ShaderResourceView> m_shaderResourceView;

	DirectX::TexMetadata m_metadata;
};
