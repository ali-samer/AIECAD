#pragma once

#include <vector>
#include <memory>
#include <iterator>

#include <aiecad/core/Layer.hpp>

namespace aiecad {

class LayerStack {
public:
	using LayerPtr = std::unique_ptr<Layer>;
	using Container = std::vector<LayerPtr>;

	LayerStack();
	~LayerStack();

	LayerStack(const LayerStack&) = delete;
	LayerStack& operator=(const LayerStack&) = delete;
	LayerStack(LayerStack&&) = delete;
	LayerStack& operator=(LayerStack&&) = delete;

	void pushLayer(LayerPtr layer);
	void pushOverlay(LayerPtr overlay);

	void popLayer(Layer* layer);
	void popOverlay(Layer* overlay);

	// iteration over all layers (layers first, then overlays)
	Container::iterator begin() { return m_layers.begin(); }
	Container::iterator end()   { return m_layers.end(); }

	Container::const_iterator begin() const { return m_layers.begin(); }
	Container::const_iterator end()   const { return m_layers.end(); }

private:
	Container m_layers;
	std::size_t m_layerInsertIndex{0};
};

} // namespace aiecad