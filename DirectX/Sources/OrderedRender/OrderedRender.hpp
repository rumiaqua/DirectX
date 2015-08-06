# pragma once

# include <set>

# include "RenderingOrder/RenderingOrder.hpp"

class OrderedRender
{
private:

	OrderedRender() = delete;

	OrderedRender(const OrderedRender&) = delete;

	OrderedRender& operator = (const OrderedRender&) = delete;

public:

	static void Initialize()
	{
		m_renderingOrders.clear();
	}

	static void Regist(float alpha, float zOrder, const std::function<void()>& renderFunc)
	{
		m_renderingOrders.emplace_back(alpha, zOrder, renderFunc);
	}

	static void Render()
	{
		std::sort(m_renderingOrders.begin(), m_renderingOrders.end());
		for (const auto& target : m_renderingOrders)
		{
			target.renderFunc();
		}

		Initialize();
	}

private:

	static std::vector<RenderingOrder> m_renderingOrders;
};

std::vector<RenderingOrder> OrderedRender::m_renderingOrders;
