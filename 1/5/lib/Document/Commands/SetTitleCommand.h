#pragma once

#include "./../../Command/AbstractUndoableEdit.h"
#include "./../DocumentItem.h"
#include <utility>
#include <vector>
#include <optional>
#include "./../IDocument.h"

class SetTitleCommand : public undo::AbstractUndoableEdit
{
public:
    SetTitleCommand(std::string& oldTitle, std::string newTitle): m_oldTitle(oldTitle), m_newTitle(newTitle)
    {
    }

    void RedoImpl() override
    {
        std::swap(m_oldTitle, m_newTitle);
    }

    void UndoImpl() override
    {
        std::swap(m_oldTitle, m_newTitle);
    }

    bool ReplaceEditImpl(const undo::IUndoableEditPtr& edit) override
    {
        if (auto otherSet = std::dynamic_pointer_cast<SetTitleCommand>(edit); otherSet && otherSet->m_newTitle == m_oldTitle)
        {
            m_oldTitle = otherSet->m_oldTitle;
            return true;
        }
        return false;
    }

private:
    std::string m_oldTitle;
    std::string m_newTitle;
};