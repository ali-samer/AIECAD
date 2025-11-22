#include <aiecad/ui/menu/ToolsMenuItem.hpp>
#include <aiecad/ui/panels/DeviceConnectionPanel.hpp>
#include <aiecad/core/events/Events.hpp>

#include <imgui.h>

#include "aiecad/ui/panels/ProjectExplorer.hpp"

namespace aiecad {

void ToolsMenuItem::onDrawMenuContents() {
	populatePanel<DeviceConnectionPanel>();
	populatePanel<ProjectExplorer>();
}

} // namespace aiecad