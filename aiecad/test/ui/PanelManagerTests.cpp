#include <aiecad/portability/GTest.hpp>

#define private public
#include <aiecad/ui/panels/PanelManager.hpp>
#undef private

#include <algorithm>
#include <memory>

using namespace aiecad;

class PanelManagerTests : public ::testing::Test {
protected:
    PanelManagerTests()
        : bus(std::make_unique<EventBus>())
        , mgr(*bus) {}
    struct FakePanel final : public UIPanel {
        FakePanel(const char* id, PanelCategory cat, bool initiallyVisible = true)
            : m_id(id), m_cat(cat), m_visible(initiallyVisible) {}

        const char* id() const noexcept override    { return m_id; }
        const char* title() const noexcept override { return m_id; } // simple for test
        PanelCategory category() const noexcept override { return m_cat; }

        bool& visible() noexcept override { return m_visible; }

        void onImGuiRender() override { ++renderCount; }

        const char*   m_id;
        PanelCategory m_cat;
        bool          m_visible;
        int           renderCount{0};
    };

    std::unique_ptr<EventBus> bus;
    PanelManager mgr;
};

TEST_F(PanelManagerTests, CanRegisterPanelsAndQueryVisibility) {
    auto p1 = std::make_unique<FakePanel>("p1", PanelCategory::Tool);
    auto p2 = std::make_unique<FakePanel>("p2", PanelCategory::Editor, false);

    EXPECT_FALSE(mgr.isVisible("p1"));
    EXPECT_FALSE(mgr.isVisible("p2"));

    mgr.registerPanel(std::move(p1));
    mgr.registerPanel(std::move(p2));

    EXPECT_TRUE(mgr.hasPanel("p1"));
    EXPECT_TRUE(mgr.hasPanel("p2"));

    EXPECT_TRUE(mgr.isVisible("p1"));   // default true
    EXPECT_FALSE(mgr.isVisible("p2"));  // default false
}

TEST_F(PanelManagerTests, CanSetVisibilityAndToggle) {
    auto p = std::make_unique<FakePanel>("p", PanelCategory::Tool, false);
    mgr.registerPanel(std::move(p));

    EXPECT_FALSE(mgr.isVisible("p"));
    mgr.setVisible("p", true);
    EXPECT_TRUE(mgr.isVisible("p"));
    mgr.toggle("p");
    EXPECT_FALSE(mgr.isVisible("p"));
}

TEST_F(PanelManagerTests, RenderCallsOnlyVisiblePanels) {
    auto p1 = std::make_unique<FakePanel>("p1", PanelCategory::Tool, true);
    auto p2 = std::make_unique<FakePanel>("p2", PanelCategory::Editor, false);

    auto* raw1 = p1.get();
    auto* raw2 = p2.get();

    mgr.registerPanel(std::move(p1));
    mgr.registerPanel(std::move(p2));

    mgr.renderVisiblePanels();

    EXPECT_EQ(raw1->renderCount, 1);
    EXPECT_EQ(raw2->renderCount, 0);

    mgr.setVisible("p2", true);
    mgr.renderVisiblePanels();

    EXPECT_EQ(raw1->renderCount, 2);
    EXPECT_EQ(raw2->renderCount, 1);
}

TEST_F(PanelManagerTests, UnknownPanelOperationsAreNoOps) {
    EXPECT_FALSE(mgr.hasPanel("does_not_exist"));
    EXPECT_FALSE(mgr.isVisible("does_not_exist"));

    mgr.setVisible("does_not_exist", true);
    mgr.toggle("does_not_exist");
    mgr.renderVisiblePanels(); // should not crash
}