#include <aiecad/core/LayerStack.hpp>
#include <algorithm>

namespace aiecad {

LayerStack::~LayerStack() {
	// unique_ptr will destroy layers automatically; we just give them
	// a chance to detach first.
	for (auto& layer : m_layers) {
		if (layer) {
			layer->onDetach();
		}
	}
}

void LayerStack::pushLayer(LayerPtr layer) {
	// Insert before first overlay.
	Layer* raw = layer.get();
	m_layers.insert(m_layers.begin() + static_cast<std::ptrdiff_t>(m_overlayInsertIndex),
					std::move(layer));
	++m_overlayInsertIndex;
	raw->onAttach();
}

void LayerStack::pushOverlay(LayerPtr overlay) {
	Layer* raw = overlay.get();
	m_layers.emplace_back(std::move(overlay));
	raw->onAttach();
}

void LayerStack::popLayer(Layer* layer) {
	auto it = std::find_if(
		m_layers.begin(),
		m_layers.begin() + static_cast<std::ptrdiff_t>(m_overlayInsertIndex),
		[layer](const LayerPtr& ptr) { return ptr.get() == layer; }
	);
	if (it != m_layers.begin() + static_cast<std::ptrdiff_t>(m_overlayInsertIndex)) {
		(*it)->onDetach();
		m_layers.erase(it);
		--m_overlayInsertIndex;
	}
}

void LayerStack::popOverlay(Layer* overlay) {
	auto it = std::find_if(
		m_layers.begin() + static_cast<std::ptrdiff_t>(m_overlayInsertIndex),
		m_layers.end(),
		[overlay](const LayerPtr& ptr) { return ptr.get() == overlay; }
	);
	if (it != m_layers.end()) {
		(*it)->onDetach();
		m_layers.erase(it);
	}
}

} // namespace aiecad