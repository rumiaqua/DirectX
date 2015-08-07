# pragma once

# include "RenderObject.hpp"

# include "Model/Model.hpp"

class RenderModel : public RenderObject
{
public:

	RenderModel(
		const std::shared_ptr<aqua::Polygon>& model)
		: m_model(model)
	{

	}

private:

	virtual void OnUpdate() = 0;

	virtual void OnRender() const = 0;

protected:

	std::shared_ptr<aqua::Polygon> m_model;
};
