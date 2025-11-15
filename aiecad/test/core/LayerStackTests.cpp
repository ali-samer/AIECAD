#include <aiecad/portability/GTest.hpp>

#include <memory>
#include <string>

/* IMPORTANT NOTE!
 *
 *  The LayerStack is the sole owner of all layers it possess in its container, which means
 *  we won't be able to test if a layer `Detaches` from the LayerStack after calling
 *  `layerStack.popLayer( layer: layerPtr )` because memory is released before we could check
 *  if the operation was successful.
 *
 *  To solve this problem, we just introduce a global variable to keep track of the
 *  number of detachment operations
 *
 *  These tests are still valid
 */

#include <aiecad/core/Layer.hpp>
#include <aiecad/core/LayerStack.hpp>

using namespace aiecad;
static int detachedCounter {0};

class TestLayer : public Layer {
public:
    explicit TestLayer(std::string name)
        : Layer(std::move(name)) {}

    void onAttach() override {
        attached = true;
        attachCount++;
    }

    void onDetach() override {
        detached = true;
        detachedCounter++;
        detachCount++;
    }

    void onUpdate(float) override {
        updateCount++;
    }

    void onImGuiRender() override {
        imguiCount++;
    }

    bool attached{false};
    bool detached{false};
    int attachCount{0};
    int detachCount{0};
    int updateCount{0};
    int imguiCount{0};
};

TEST(LayerStackBasic, PushLayerCallsOnAttach) {
    LayerStack stack;

    auto layer = std::make_unique<TestLayer>("Test");
    auto* rawPtr = layer.get();

    EXPECT_FALSE(rawPtr->attached);
    EXPECT_EQ(rawPtr->attachCount, 0);

    stack.pushLayer(std::move(layer));

    EXPECT_TRUE(rawPtr->attached);
    EXPECT_EQ(rawPtr->attachCount, 1);
}

TEST(LayerStackBasic, PopLayerCallsOnDetach) {
    LayerStack stack;

    auto layer = std::make_unique<TestLayer>("Test");
    auto* rawPtr = layer.get();
    detachedCounter = 0;

    stack.pushLayer(std::move(layer));
    EXPECT_FALSE(rawPtr->detached);
    EXPECT_EQ(rawPtr->detachCount, 0);
    EXPECT_EQ(detachedCounter, 0);

    stack.popLayer(rawPtr);

    EXPECT_EQ(detachedCounter, 1);
}

TEST(LayerStackBasic, DestroyStackDetachesLayers) {
    auto layer = std::make_unique<TestLayer>("Test");
    auto* rawPtr = layer.get();
    detachedCounter = 0;

    {
        LayerStack stack;
        stack.pushLayer(std::move(layer));
        EXPECT_FALSE(rawPtr->detached);
        EXPECT_EQ(rawPtr->detachCount, 0);
        EXPECT_EQ(detachedCounter, 0);
    } // stack destroyed here

    EXPECT_EQ(detachedCounter, 1);
}

TEST(LayerStackBasic, OverlaysAreAfterLayers) {
    LayerStack stack;

    auto base1 = std::make_unique<TestLayer>("Base1");
    auto base2 = std::make_unique<TestLayer>("Base2");
    auto overlay = std::make_unique<TestLayer>("Overlay");

    auto* base1Ptr = base1.get();
    auto* base2Ptr = base2.get();
    auto* overlayPtr = overlay.get();

    stack.pushLayer(std::move(base1));
    stack.pushLayer(std::move(base2));
    stack.pushOverlay(std::move(overlay));

    // Iteration: Base1, Base2, Overlay
    auto it = stack.begin();
    ASSERT_NE(it, stack.end());
    EXPECT_EQ((*it).get(), base1Ptr);
    ++it;
    ASSERT_NE(it, stack.end());
    EXPECT_EQ((*it).get(), base2Ptr);
    ++it;
    ASSERT_NE(it, stack.end());
    EXPECT_EQ((*it).get(), overlayPtr);
    ++it;
    EXPECT_EQ(it, stack.end());
}