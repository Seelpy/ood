#pragma once

#include <iostream>
#include <sstream>
#include "IGumballMachine.h"
#include "IAdminGumballMachine.h"
#include "States/IState.h"
#include "States/SoldState.h"
#include "States/SoldOutState.h"
#include "States/NoQuarterState.h"
#include "States/HasQuarterState.h"

class GumballMachine : private IGumballMachine, private IAdminGumballMachine
{
public:
    explicit GumballMachine(unsigned numBalls)
            : m_soldState(*this), m_soldOutState(*this), m_noQuarterState(*this), m_hasQuarterState(*this),
              m_state(&m_soldOutState), m_count(numBalls)
    {
        if (m_count > 0)
        {
            m_state = &m_noQuarterState;
        }
        else
        {
            m_state = &m_soldOutState;
        }
    }

    void EjectQuarter()
    {
        m_state->EjectQuarter();
    }

    void InsertQuarter()
    {
        m_state->InsertQuarter();
    }

    void TurnCrank()
    {
        m_state->TurnCrank();
        m_state->Dispense();
    }

    [[nodiscard]] std::string ToString() const
    {
        std::ostringstream oss;
        oss << R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: )" << m_count << " gumball" << (m_count != 1 ? "s" : "")
            << R"(
Machine is )" << m_state->ToString() << std::endl;
        return oss.str();
    }

private:
    [[nodiscard]] unsigned GetBallCount() const override
    {
        return m_count;
    }

    void ReleaseBall() override
    {
        if (m_count != 0)
        {
            std::cout << "A gumball comes rolling out the slot...\n";
            --m_count;
        }
    }

    [[nodiscard]] unsigned GetQuarterCount() const override
    {
        return m_quarter;
    }

    [[nodiscard]] unsigned GetMaxQuarterCount() const override
    {
        return MAX_QUARTER;
    }

    void AddQuarter() override
    {
        ++m_quarter;
    }

    void ReturnAllQuarters() override
    {
        std::cout << "Return all quarters\n";

        m_quarter = 0;
    }

    void SetSoldOutState() override
    {
        m_state = &m_soldOutState;
    }

    void SetNoQuarterState() override
    {
        m_state = &m_noQuarterState;
    }

    void SetSoldState() override
    {
        m_state = &m_soldState;
    }

    void SetHasQuarterState() override
    {
        m_state = &m_hasQuarterState;
    }

    void AddGumballs(unsigned count) override
    {
        m_count += count;
    }

    void InsertGumballs(unsigned count) override
    {
        m_state->InsertGumballs(count);
    }


private:
    static constexpr unsigned MAX_QUARTER = 5;
    unsigned m_count = 0;
    unsigned m_quarter = 0;
    SoldState m_soldState{*this};
    SoldOutState m_soldOutState{*this};
    NoQuarterState m_noQuarterState{*this};
    HasQuarterState m_hasQuarterState{*this};
    IState *m_state{};
};
