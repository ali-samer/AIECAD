#include <aiecad/Portability.h>
#include <aiecad/portability/GTest.hpp>


AIECAD_ATTR_WEAK int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}