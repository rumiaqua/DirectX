# pragma once

// 順序描画オブジェクト
struct RenderingOrder
{
	// アルファ値
	float alpha;

	// Zオーダー
	float zOrder;

	// 描画処理
	std::function<void()> renderFunc;

	// コンストラクタ
	RenderingOrder(float alpha, float zOrder, const std::function<void()>& renderFunc)
		: alpha(alpha)
		, zOrder(zOrder)
		, renderFunc(renderFunc)
	{

	}

	// 比較演算子
	bool operator > (const RenderingOrder& other) const
	{
		if (this->alpha == 1.0f)
			return false;

		if (other.alpha == 1.0f)
			return true;

		return other.zOrder > this->zOrder;
	}
	bool operator < (const RenderingOrder& other) const
	{
		return other > *this;
	}
};
