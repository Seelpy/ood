#pragma once

class IGumballMachine
{
public:
    virtual void ReleaseBall() = 0;

    [[nodiscard]] virtual unsigned GetBallCount() const = 0;

    [[nodiscard]] virtual unsigned GetQuarterCount() const = 0;

    [[nodiscard]] virtual unsigned GetMaxQuarterCount() const = 0;

    virtual void AddQuarter() = 0;

    virtual void ReturnAllQuarters() = 0;

    virtual void SetSoldOutState() = 0;

    virtual void SetNoQuarterState() = 0;

    virtual void SetSoldState() = 0;

    virtual void SetHasQuarterState() = 0;

    virtual void AddGumballs(unsigned count) = 0;

    virtual ~IGumballMachine() = default;
};