#include <swag/Portability.h>
#include <swag/portability/GTest.hpp>


SWAG_ATTR_WEAK int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}