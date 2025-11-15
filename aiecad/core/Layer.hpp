#pragma once

#include <string>

namespace aiecad {

class Layer {
public:
	explicit Layer(std::string name)
		: m_name(std::move(name)) {}

	virtual ~Layer() = default;

	Layer(const Layer&) = delete;
	Layer& operator=(const Layer&) = delete;
	Layer(Layer&&) = delete;
	Layer& operator=(Layer&&) = delete;

	virtual void onAttach() {}
	virtual void onDetach() {}
	virtual void onUpdate(float /*deltaTime*/) {}
	virtual void onImGuiRender() {}

	const std::string& getName() const { return m_name; }

private:
	std::string m_name;
};

} // namespace aiecad