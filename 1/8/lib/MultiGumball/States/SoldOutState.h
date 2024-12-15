#pragma once

#include "IState.h"
#include "../IGumballMachine.h"

class SoldOutState : public IState
{
public:
    explicit SoldOutState(IGumballMachine &gumballMachine)
            : m_gumballMachine(gumballMachine)
    {}

    void InsertQuarter() override
    {
        std::cout << "You can't insert a quarter, the machine is sold out\n";
    }

    void EjectQuarter() override
    {
        std::cout << "Quarter returned\n";
        m_gumballMachine.ReturnAllQuarters();
        // TODO: оставаться в том же состоянии
        m_gumballMachine.SetNoQuarterState();
    }

    void TurnCrank() override
    {
        std::cout << "You turned but there's no gumballs\n";
    }

    void Dispense() override
    {
        std::cout << "No gumball dispensed\n";
    }

    void InsertGumballs(unsigned count) override
    {
        std::cout << "Added gumballs\n";
        m_gumballMachine.AddGumballs(count);
        if (m_gumballMachine.GetBallCount() > 0)
        {
            if (m_gumballMachine.GetQuarterCount() > 0)
            {
                m_gumballMachine.SetHasQuarterState();
            }
            else
            {
                m_gumballMachine.SetNoQuarterState();
            }
        }
    }

    [[nodiscard]] std::string ToString() const override
    {
        return "sold out";
    }

private:
    IGumballMachine &m_gumballMachine;
};
