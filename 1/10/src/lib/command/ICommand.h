#pragma once

#include <memory>

class ICommand
{
public:
    virtual ~ICommand() = default;

    virtual void Redo() = 0;

    virtual void Undo() = 0;

    virtual void Destroy() = 0;
};

typedef std::shared_ptr<ICommand> ICommandPtr;