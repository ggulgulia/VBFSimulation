#include <VBF_World.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using VBF::World;
using ::testing::Eq;


/*! Test fixture for testing the vbf world so that in subsequent
 * tests, manual set up of the VBF::World object is not needed
 */
class Test_VBF_World : public testing::Test{
    public:
        World* vbf_world;
        virtual void SetUp(){
            vbf_world = new World();
            vbf_world->intialize_new_world();
        }

        virtual void TearDown(){
            delete vbf_world;
            vbf_world = nullptr;
        }
};

TEST_F(Test_VBF_World, worldIsInitialized){
    SetUp();
    ASSERT_THAT(vbf_world->is_initialized(), Eq(true));
}

TEST_F(Test_VBF_World, timeIsInitializedToZero){
    SetUp();
    ASSERT_THAT(vbf_world->get_curr_time(), Eq(0.0));
}
