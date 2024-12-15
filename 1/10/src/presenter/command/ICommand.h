#pragma once

class ICommand
{
public:
    virtual ~ICommand();

    virtual void Redo();

    virtual void Undo();

    virtual void Destroy();
};