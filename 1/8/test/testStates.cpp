#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./../lib/Gumball/GumballMachine.h"

class GumballMachineTest : public ::testing::Test
{
protected:
    GumballMachine gumballMachine{5};
    std::streambuf *originalCout{};
    std::ostringstream testOutput;

    void SetUp() override
    {
        originalCout = std::cout.rdbuf(testOutput.rdbuf());
    }

    void TearDown() override
    {
        std::cout.rdbuf(originalCout);
    }
};

class MockGumballMachine : public IGumballMachine
{
public:
    MOCK_METHOD(void, ReleaseBall, (), (override));
    MOCK_METHOD(unsigned, GetBallCount, (), (const, override));
    MOCK_METHOD(void, SetSoldOutState, (), (override));
    MOCK_METHOD(void, SetNoQuarterState, (), (override));
    MOCK_METHOD(void, SetSoldState, (), (override));
    MOCK_METHOD(void, SetHasQuarterState, (), (override));
};

TEST_F(GumballMachineTest, Mock_NoQuarterState_InsertQuarter)
{
    MockGumballMachine mockGumballMachine;
    NoQuarterState state = NoQuarterState(mockGumballMachine);

    EXPECT_CALL(mockGumballMachine, SetHasQuarterState()).Times(1);

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You inserted a quarter\n");
}

TEST_F(GumballMachineTest, Mock_NoQuarterState_EjectQuarter)
{
    MockGumballMachine mockGumballMachine;
    NoQuarterState state = NoQuarterState(mockGumballMachine);

    state.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "You haven't inserted a quarter\n");
}

TEST_F(GumballMachineTest, Mock_NoQuarterState_TurnCrank)
{
    MockGumballMachine mockGumballMachine;
    NoQuarterState state = NoQuarterState(mockGumballMachine);

    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You turned but there's no quarter\n");
}

TEST_F(GumballMachineTest, Mock_NoQuarterState_Dispense)
{
    MockGumballMachine mockGumballMachine;
    NoQuarterState state = NoQuarterState(mockGumballMachine);

    state.Dispense();
    EXPECT_EQ(testOutput.str(), "You need to pay first\n");
}

TEST_F(GumballMachineTest, Mock_NoQuarterState_ToString)
{
    MockGumballMachine mockGumballMachine;
    NoQuarterState state = NoQuarterState(mockGumballMachine);

    std::string actualString = state.ToString();
    EXPECT_EQ(actualString, "waiting for quarter");
}

// HasQuarterState
TEST_F(GumballMachineTest, Mock_HasQuarterState_InsertQuarter)
{
    MockGumballMachine mockGumballMachine;
    HasQuarterState state = HasQuarterState(mockGumballMachine);

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You can't insert another quarter\n");
}

TEST_F(GumballMachineTest, Mock_HasQuarterState_EjectQuarter)
{
    MockGumballMachine mockGumballMachine;
    HasQuarterState state = HasQuarterState(mockGumballMachine);

    EXPECT_CALL(mockGumballMachine, SetNoQuarterState).Times(1);

    state.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "Quarter returned\n");
}

TEST_F(GumballMachineTest, Mock_HasQuarterState_TurnCrank)
{
    MockGumballMachine mockGumballMachine;
    HasQuarterState state = HasQuarterState(mockGumballMachine);

    EXPECT_CALL(mockGumballMachine, SetSoldState).Times(1);

    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You turned...\n");
}

TEST_F(GumballMachineTest, Mock_HasQuarterState_Dispense)
{
    MockGumballMachine mockGumballMachine;
    HasQuarterState state = HasQuarterState(mockGumballMachine);

    state.Dispense();
    EXPECT_EQ(testOutput.str(), "No gumball dispensed\n");
}

TEST_F(GumballMachineTest, Mock_HasQuarterState_ToString)
{
    MockGumballMachine mockGumballMachine;
    HasQuarterState state = HasQuarterState(mockGumballMachine);

    std::string actualString = state.ToString();
    EXPECT_EQ(actualString, "waiting for turn of crank");
}

// SoldState
TEST_F(GumballMachineTest, Mock_SoldState_InsertQuarter)
{
    MockGumballMachine mockGumballMachine;
    SoldState state = SoldState(mockGumballMachine);

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "Please wait, we're already giving you a gumball\n");
}

TEST_F(GumballMachineTest, Mock_SoldState_EjectQuarter)
{
    MockGumballMachine mockGumballMachine;
    SoldState state = SoldState(mockGumballMachine);

    state.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "Sorry you already turned the crank\n");
}

TEST_F(GumballMachineTest, Mock_SoldState_TurnCrank)
{
    MockGumballMachine mockGumballMachine;
    SoldState state = SoldState(mockGumballMachine);

    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "Turning twice doesn't get you another gumball\n");
}

TEST_F(GumballMachineTest, Mock_SoldState_Dispense)
{
    MockGumballMachine mockGumballMachine;
    SoldState state = SoldState(mockGumballMachine);

    EXPECT_CALL(mockGumballMachine, ReleaseBall).Times(1);
    EXPECT_CALL(mockGumballMachine, GetBallCount())
            .WillOnce(testing::Return(1));
    EXPECT_CALL(mockGumballMachine, SetNoQuarterState).Times(1);

    state.Dispense();

    EXPECT_CALL(mockGumballMachine, ReleaseBall).Times(1);
    EXPECT_CALL(mockGumballMachine, GetBallCount())
            .WillOnce(testing::Return(0));
    EXPECT_CALL(mockGumballMachine, SetSoldOutState).Times(1);

    state.Dispense();
}

TEST_F(GumballMachineTest, Mock_SoldState_ToString)
{
    MockGumballMachine mockGumballMachine;
    SoldState state = SoldState(mockGumballMachine);

    std::string actualString = state.ToString();
    EXPECT_EQ(actualString, "delivering a gumball");
}

TEST_F(GumballMachineTest, Mock_SoldOutState_InsertQuarter)
{
    MockGumballMachine mockGumballMachine;
    SoldOutState state = SoldOutState(mockGumballMachine);

    state.InsertQuarter();
    EXPECT_EQ(testOutput.str(), "You can't insert a quarter, the machine is sold out\n");
}

TEST_F(GumballMachineTest, Mock_SoldOutState_EjectQuarter)
{
    MockGumballMachine mockGumballMachine;
    SoldOutState state = SoldOutState(mockGumballMachine);

    state.EjectQuarter();
    EXPECT_EQ(testOutput.str(), "You can't eject, you haven't inserted a quarter yet\n");
}

TEST_F(GumballMachineTest, Mock_SoldOutState_TurnCrank)
{
    MockGumballMachine mockGumballMachine;
    SoldOutState state = SoldOutState(mockGumballMachine);

    state.TurnCrank();
    EXPECT_EQ(testOutput.str(), "You turned but there's no gumballs\n");
}

TEST_F(GumballMachineTest, Mock_SoldOutState_Dispense)
{
    MockGumballMachine mockGumballMachine;
    SoldOutState state = SoldOutState(mockGumballMachine);

    state.Dispense();
    EXPECT_EQ(testOutput.str(), "No gumball dispensed\n");
}

TEST_F(GumballMachineTest, Mock_SoldOutState_ToString)
{
    MockGumballMachine mockGumballMachine;
    SoldOutState state = SoldOutState(mockGumballMachine);

    std::string actualString = state.ToString();
    EXPECT_EQ(actualString, "sold out");
}