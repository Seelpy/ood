#pragma once

#include "ICommand.h"

class IExecuter
{
    virtual void AddAndExecuteCommand(ICommandPtr command) = 0;
};