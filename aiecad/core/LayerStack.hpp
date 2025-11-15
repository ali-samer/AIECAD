#pragma once

#include <aiecad/core/Layer.hpp>

#include <vector>

namespace aiecad {
using LayerPtr = std::unique_ptr<Layer>;
class LayerStack {
public:
	LayerStack() = default;
	~LayerStack();

	using Container              = std::vector<LayerPtr>;
	using iterator               = Container::iterator;
	using const_iterator         = Container::const_iterator;
	using reverse_iterator       = Container::reverse_iterator;
	using const_reverse_iterator = Container::const_reverse_iterator;

	Container& getLayers() { return m_layers; }

	void pushLayer(LayerPtr layer);
	void popLayer(Layer* layer);
	void pushOverlay(LayerPtr overlay);
	void popOverlay(Layer* overlay);

	iterator       begin() { return m_layers.begin(); }
	iterator       end() { return m_layers.end(); }
	const_iterator begin() const { return m_layers.begin(); }
	const_iterator end() const { return m_layers.end(); }

	/* For reverse iteration (topmost layer first). */
	reverse_iterator       rbegin() { return m_layers.rbegin(); }
	reverse_iterator       rend() { return m_layers.rend(); }
	const_reverse_iterator rbegin() const { return m_layers.rbegin(); }
	const_reverse_iterator rend() const { return m_layers.rend(); }

private:
	Container   m_layers;
	std::size_t m_overlayInsertIndex{ 0 };
};
} // namespace aiecad
