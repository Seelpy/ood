#pragma once

#include "./../../Command/AbstractUndoableEdit.h"
#include "./../DocumentItem.h"
#include <utility>
#include <vector>
#include <optional>
#include "./../Paragraph/Paragraph.h"
#include "InsertDocumentItemCommand.h"

class ReplaceTextCommand : public undo::AbstractUndoableEdit
{
public:
    ReplaceTextCommand(
            std::vector<DocumentItem> &items,
            size_t index,
            std::string newText
    ) : m_items(items), m_newText(std::move(newText)), m_index(index)
    {
    }

    void RedoImpl() override
    {
        if (auto paragraph = m_items.at(m_index).GetParagraph(); paragraph != nullptr)
        {
            if (m_oldText.empty())
            {
                m_oldText = paragraph->GetText();
            }
            paragraph->SetText(m_newText);
        }
        else
        {
            throw std::logic_error("cant replace text");
        }
    }

    void UndoImpl() override
    {
        if (auto paragraph = m_items.at(m_index).GetParagraph(); paragraph != nullptr)
        {
            paragraph->SetText(m_oldText);
        }
        else
        {
            throw std::logic_error("cant unde replace text");
        }
    }

    bool ReplaceEditImpl(const undo::IUndoableEditPtr &edit) override
    {
        if (auto otherReplace = std::dynamic_pointer_cast<ReplaceTextCommand>(edit); otherReplace)
        {
            if (otherReplace->m_index == m_index)
            {
                m_oldText = otherReplace->m_oldText;
                return true;
            }
        }
        return false;
    }

private:
    std::vector<DocumentItem> & m_items;
    size_t m_index;
    std::string m_oldText;
    std::string m_newText;
};