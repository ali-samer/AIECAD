#include <iostream>
#include <ostream>
#include <aiecad/core/LayerStack.hpp>

namespace aiecad {

LayerStack::LayerStack() = default;

LayerStack::~LayerStack() {
	for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
		if (*it) {
			(*it)->onDetach();
		}
	}
}

void LayerStack::pushLayer(LayerPtr layer) {
	if (!layer) {
		return;
	}

	layer->onAttach();
	m_layers.insert(m_layers.begin() + static_cast<std::ptrdiff_t>(m_layerInsertIndex),
					std::move(layer));
	++m_layerInsertIndex;
}

void LayerStack::pushOverlay(LayerPtr overlay) {
	if (!overlay) {
		return;
	}

	overlay->onAttach();
	m_layers.emplace_back(std::move(overlay));
}

void LayerStack::popLayer(Layer* layer) {
	if (!layer) {
		std::cerr << "LayerStack::popLayer: layer is null" << std::endl;
		return;
	}

	for (std::size_t i = 0; i < m_layerInsertIndex; ++i) {
		if (m_layers[i].get() == layer) {
			m_layers[i]->onDetach();
			m_layers.erase(m_layers.begin() + static_cast<std::ptrdiff_t>(i));
			--m_layerInsertIndex;
			return;
		}
	}
}

void LayerStack::popOverlay(Layer* overlay) {
	if (!overlay) {
		return;
	}

	for (std::size_t i = m_layerInsertIndex; i < m_layers.size(); ++i) {
		if (m_layers[i].get() == overlay) {
			m_layers[i]->onDetach();
			m_layers.erase(m_layers.begin() + static_cast<std::ptrdiff_t>(i));
			return;
		}
	}
}

} // namespace aiecad