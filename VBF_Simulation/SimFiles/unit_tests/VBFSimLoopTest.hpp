#include <VBF_SimLoop.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using VBF::SimLoop;
using namespace testing;

class SimLoopTest : public Test{
    public:
        SimLoop sim_loop;
};

TEST_F(SimLoopTest, CurrTimeAtBeginIsZero){

    ASSERT_THAT(sim_loop.get_curr_time(), Eq(0.0));
}

TEST_F(SimLoopTest, NumStepsAtBeginIsZero){
    ASSERT_THAT(sim_loop.get_num_steps(), Eq(0));
}

TEST_F(SimLoopTest,AdvanceTimeByDeltaT){
    sim_loop.step(0.1);
    ASSERT_THAT(sim_loop.get_curr_time(), Eq(0.1));
    ASSERT_THAT(sim_loop.get_num_steps(), Eq(1));
}
