#pragma once

#include <aiecad/ui/menu/GlobalMenuItem.hpp>
#include <aiecad/macros/Macros.hpp>

#include <memory>
#include <vector>

namespace aiecad {

class GlobalMenuBar {
public:
	GlobalMenuBar() = default;
	~GlobalMenuBar() = default;

	AIECAD_DELETE_COPY_AND_MOVE(GlobalMenuBar);

	void registerItem(std::unique_ptr<GlobalMenuItem> item);
	void render();

private:
	std::vector<std::unique_ptr<GlobalMenuItem>> m_items;
};

} // namespace aiecad