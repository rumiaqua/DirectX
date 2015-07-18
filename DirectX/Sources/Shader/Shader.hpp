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

	static void SetEffect(ID3DX11Effect* effect)
	{
		Instance().m_effect = effect;
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

	ID3DX11Effect* m_effect;

	std::unordered_map<std::wstring, ID3DX11EffectVariable*> m_variable;
};
