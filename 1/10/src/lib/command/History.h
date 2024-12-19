#pragma once

#include "ICommand.h"
#include <vector>
#include "IExecuter.h"
#include "IHistory.h"

// TODO: перенести в lib

class History: public IExecuter, public IHistory
{
public:
    History() = default;

    void AddAndExecuteCommand(ICommandPtr command) override
    {
        m_commands.insert(m_commands.begin() + m_state + 1, command);
        Redo();
    }

    bool CanRedo() override
    {
        return m_state < m_commands.size();
    }

    void Redo() override
    {
        if (CanRedo())
        {
            m_state++;
            m_commands.at(m_state)->Redo();
        }
    }

    bool CanUndo() override
    {
        return m_state < m_commands.size() && m_state >= 0;
    }

    void Undo() override
    {
        if (CanUndo())
        {
            m_commands.at(m_state)->Redo();
            m_state--;
        }
    }

private:
    std::vector<ICommandPtr> m_commands;
    int m_state = 0;
};