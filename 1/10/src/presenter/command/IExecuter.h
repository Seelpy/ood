#pragma once

#include "ICommand.h"

class IExecuter {
    virtual void AddAndExecuteCommand(ICommand command);
};