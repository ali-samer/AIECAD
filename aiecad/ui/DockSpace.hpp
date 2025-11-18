#pragma once

#include <aiecad/core/Layer.hpp>

namespace aiecad {

class DockSpace final : public Layer {
public:
	DockSpace();
	~DockSpace() override = default;

	void onAttach() override {}
	void onDetach() override {}

	void onUpdate(float) override {}
	void onImGuiRender() override;
};

} // namespace aiecad