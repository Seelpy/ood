#pragma once

class IHistory
{
public:
    virtual ~IHistory() = default;

    virtual bool CanRedo() = 0;

    virtual void Redo() = 0;

    virtual bool CanUndo() = 0;

    virtual void Undo() = 0;
};