#pragma once

#include "ICommand.h"
#include <vector>

class MultiCommand : public ICommand
{
public:
    MultiCommand(std::vector<ICommand> commands)
    {
        m_commands = commands;
    }

    ~MultiCommand() {
        Destroy();
    }

    void Redo() override
    {
        for (auto command: m_commands)
        {
            command.Redo();
        }
    }

    void Undo() override
    {
        for (auto command: m_commands)
        {
            command.Undo();
        }
    }

    void Destroy() override
    {
        for (auto command: m_commands)
        {
            command.Destroy();
        }
    }
private:
    std::vector<ICommand> m_commands;
};