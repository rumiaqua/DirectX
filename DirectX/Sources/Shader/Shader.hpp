# pragma once

# include "Handle/Handle.hpp"

# include "Convert/Convert.hpp"

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

public:

	static void SetEffect(ID3DX11Effect* effect)
	{
		Instance().m_effect = effect;
	}

	static ID3DX11EffectVariable* Variable(const std::wstring& name)
	{
		auto val = Instance().m_effect->GetVariableByName(ToMultibyte(name).c_str());
		if (!val->IsValid())
		{
			assert((L"‚¾‚ß‚Å‚· : " + name).c_str());
		}
		return val;
	}

private:

	ID3DX11Effect* m_effect;
};
