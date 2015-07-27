# pragma once

// �����`��I�u�W�F�N�g
struct RenderingOrder
{
	// �A���t�@�l
	float alpha;

	// Z�I�[�_�[
	float zOrder;

	// �`�揈��
	std::function<void()> renderFunc;

	// �R���X�g���N�^
	RenderingOrder(float alpha, float zOrder, const std::function<void()>& renderFunc)
		: alpha(alpha)
		, zOrder(zOrder)
		, renderFunc(renderFunc)
	{

	}

	// ��r���Z�q
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
