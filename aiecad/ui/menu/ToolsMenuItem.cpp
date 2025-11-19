#include <aiecad/ui/menu/ToolsMenuItem.hpp>
#include <aiecad/ui/panels/DeviceConnectionPanel.hpp>
#include <aiecad/core/events/Events.hpp>

#include <imgui.h>

namespace aiecad {

void ToolsMenuItem::onDrawMenuContents() {
	populatePanel<DeviceConnectionPanel>();
}

} // namespace aiecad