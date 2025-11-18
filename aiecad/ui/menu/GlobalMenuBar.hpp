#pragma once

#include <aiecad/ui/menu/GlobalMenuItem.hpp>

#include <memory>
#include <vector>

namespace aiecad {

class GlobalMenuBar {
public:
	GlobalMenuBar() = default;
	~GlobalMenuBar() = default;

	GlobalMenuBar(const GlobalMenuBar&) = delete;
	GlobalMenuBar& operator=(const GlobalMenuBar&) = delete;
	GlobalMenuBar(GlobalMenuBar&&) = delete;
	GlobalMenuBar& operator=(GlobalMenuBar&&) = delete;

	void registerItem(std::unique_ptr<GlobalMenuItem> item);
	void render();

private:
	std::vector<std::unique_ptr<GlobalMenuItem>> m_items;
};

} // namespace aiecad