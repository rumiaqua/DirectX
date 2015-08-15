# pragma once

# include <unordered_map>

# include "IResource.hpp"

class Resources
{
public:

	template <typename Type>
	static void Register(const String& name, const String& filename)
	{
		m_resources[name] = std::make_shared<Type>();
		if (!m_resources.at(name)->Load(filename))
		{
			throw std::exception("���\�[�X�̐����Ɏ��s���܂���");
		}
	}

	template <typename Type>
	static Type* Get(const String& name)
	{
		auto ptr = dynamic_cast<Type*>(m_resources.at(name).get());
		if (ptr)
		{
			return ptr;
		}
		throw std::exception("�L���Ȍ^�ϊ����s�Ȃ��܂���ł���");
	}

private:

	static std::unordered_map<String, std::shared_ptr<IResource>> m_resources;
};

std::unordered_map<String, std::shared_ptr<IResource>> Resources::m_resources;
