# pragma once

# include "Handle/Handle.hpp"

# include "Convert/Convert.hpp"

# include <unordered_map>

class Shader
{
private:

	Shader()
		: m_effect(nullptr)
	{

	}

	static Shader& Instance()
	{
		static Shader shader;
		return shader;
	}

	static bool IsCached(const std::wstring& name)
	{
		return Instance().m_variable.find(name) != Instance().m_variable.end();
	}

	static ID3DX11EffectVariable* Cache(const std::wstring& name)
	{
		return Instance().m_variable.at(name);
	}

	static ID3DX11EffectVariable* Regist(const std::wstring& name)
	{
		Instance().m_variable[name] =
			Instance().m_effect->GetVariableByName(ToMultibyte(name).c_str());

		return Cache(name);
	}

public:

	static void SetEffect(const std::wstring& filepath)
	{
		D3DX11CompileEffectFromFile(
			filepath.c_str(),
			NULL,
			NULL,
			0U,
			0U,
			Window::Device(),
			&Instance().m_effect,
			NULL);
	}

	static ID3DX11Effect* Effect()
	{
		return Instance().m_effect;
	}

	static ID3DX11EffectVariable* Variable(const std::wstring& name)
	{
		if (IsCached(name))
		{
			return Cache(name);
		}
		else
		{
			auto val =Regist(name);
			if (!val)
			{
				assert((L"‚¾‚ß‚Å‚· : " + name).c_str());
			}
			return val;
		}
	}

private:

	Handle<ID3DX11Effect> m_effect;

	std::unordered_map<std::wstring, ID3DX11EffectVariable*> m_variable;
};
