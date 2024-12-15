#pragma once

#include "IState.h"
#include "../IGumballMachine.h"

class HasQuarterState : public IState
{
public:
    explicit HasQuarterState(IGumballMachine &gumballMachine)
            : m_gumballMachine(gumballMachine)
    {}

    void InsertQuarter() override
    {
        if (m_gumballMachine.GetQuarterCount() < m_gumballMachine.GetMaxQuarterCount())
        {
            std::cout << "You insert quarter\n";
            m_gumballMachine.AddQuarter();
        }
        else
        {
            std::cout << "You can't insert quarter\n";
        }
    }

    void EjectQuarter() override
    {
        std::cout << "Quarter returned\n";
        m_gumballMachine.ReturnAllQuarters();
        m_gumballMachine.SetNoQuarterState();
    }

    void TurnCrank() override
    {
        std::cout << "You turned...\n";
        m_gumballMachine.SetSoldState();
    }

    void Dispense() override
    {
        std::cout << "No gumball dispensed\n";
    }

    void InsertGumballs(unsigned count) override
    {
        std::cout << "Added gumballs\n";
        m_gumballMachine.AddGumballs(count);
    }

    [[nodiscard]] std::string ToString() const override
    {
        return "waiting for turn of crank";
    }

private:
    IGumballMachine &m_gumballMachine;
};
