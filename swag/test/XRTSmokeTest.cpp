#include <swag/portability/GTest.hpp>
#include <xrt/xrt_device.h>   // XRT C API
#include <xrt/xrt_bo.h>
#include <xrt/xrt_kernel.h>

// Very simple smoke test: open device 0 and check it succeeds
TEST(Xrt, OpenDevice) {
    try {
        xrt::device dev{0};  // open device index 0
        // If we got here, the device handle is valid
        SUCCEED();
    }
    catch (const std::exception& ex) {
        FAIL() << "Failed to open XRT device 0: " << ex.what();
    }
}
