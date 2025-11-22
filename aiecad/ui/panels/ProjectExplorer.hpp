#pragma once

#include <imgui.h>
#include <aiecad/ui/panels/UIPanel.hpp>
#include <aiecad/utils/imfilebrowser.h>
#include <aiecad/core/events/EventSubscription.hpp>

namespace aiecad {
class EventBus;

class ProjectExplorer final : public UIPanel {
public:
	ProjectExplorer(EventBus &);
	~ProjectExplorer() = default;

	static const char* Id() noexcept { return "ProjectExplorer"; }
	static const char* Title() noexcept { return "Project Explorer"; }
	const char*        id() const noexcept override { return Id(); }

	const char*   title() const noexcept override { return "ProjectExplorer"; }
	PanelCategory category() const noexcept override { return PanelCategory::View; }

	bool& visible() noexcept override { return m_visible; }
	void  toggleVisibility() noexcept { m_visible = !m_visible; }

	void onImGuiRender() override;

private:
	bool               m_visible{ false };
	EventBus &         m_bus;
	EventSubscription  m_toggleSubEvent;
	ImGui::FileBrowser m_fileDialog;
};
} // namespace aiecad
