#pragma once

class IHistory
{
public:
    virtual ~IHistory();

    virtual bool CanRedo();

    virtual void Redo();

    virtual bool CanUndo();

    virtual void Undo();
};