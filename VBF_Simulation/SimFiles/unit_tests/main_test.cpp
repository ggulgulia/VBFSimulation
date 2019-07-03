#include <gtest/gtest.h>
#include <utility>


/*! creating a test fixture for testing the  functionalities of 
    the mars rover so that we don't need to create and destroy 
    the MarsRover::Rover object for testing every method provided 
    by the MarsRover::Rover interface
*/

int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

