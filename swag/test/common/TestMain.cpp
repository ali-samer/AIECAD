#include <swag/Portability.h>
#include <swag/portability/GTest.hpp>


int main(int argc, char **argv) SWAG_ATTR_WEAK {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}