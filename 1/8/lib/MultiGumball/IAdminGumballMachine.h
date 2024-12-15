#pragma once

class IAdminGumballMachine
{
public:
    virtual void InsertGumballs(unsigned count) = 0;

    virtual ~IAdminGumballMachine() = default;
};