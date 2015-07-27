# pragma once

# include <set>

# include "RenderingOrder/RenderingOrder.hpp"

class OrderedRender
{
private:

	OrderedRender();

	OrderedRender(const OrderedRender&);

	OrderedRender& operator = (const OrderedRender&);

public:

	static void Initialize()
	{
		m_renderingOrders.clear();
	}

	static void Regist(float alpha, float zOrder, const std::function<void()>& renderFunc)
	{
		m_renderingOrders.emplace(alpha, zOrder, renderFunc);
	}

	static void Render()
	{
		for (const auto& target : m_renderingOrders)
		{
			target.renderFunc();
		}

		Initialize();
	}

private:

	static std::set<RenderingOrder> m_renderingOrders;
};

std::set<RenderingOrder> OrderedRender::m_renderingOrders;
