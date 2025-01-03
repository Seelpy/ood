#pragma once

#include "./../../Command/AbstractUndoableEdit.h"
#include "./../DocumentItem.h"
#include <utility>
#include <vector>
#include <optional>
#include "./../Paragraph/Paragraph.h"
#include "InsertDocumentItemCommand.h"

class ResizeImageCommand : public undo::AbstractUndoableEdit
{
public:
    ResizeImageCommand(
            std::vector<DocumentItem> &items,
            size_t index,
            unsigned int newW,
            unsigned int newH
    ): m_items(items), m_newW(newW), m_newH(newH), m_index(index)
    {
    }

    void RedoImpl() override
    {
        if (auto image = m_items.at(m_index).GetImage(); image != nullptr)
        {
            if (m_oldW == 0 || m_oldH == 0)
            {
                m_oldW = image->GetWidth();
                m_oldH = image->GetHeight();
            }
            image->Resize(m_newW, m_newH);
        }
        else
        {
            throw std::logic_error("cant resize");
        }
    }

    void UndoImpl() override
    {
        if (auto image = m_items.at(m_index).GetImage(); image != nullptr)
        {
            image->Resize(m_oldW, m_oldH);
        }
        else
        {
            throw std::logic_error("cant undo resize");
        }
    }

    bool ReplaceEditImpl(const undo::IUndoableEditPtr& edit) override
    {
        if (auto otherReplace = std::dynamic_pointer_cast<ResizeImageCommand>(edit); otherReplace)
        {
            if (otherReplace->m_index == m_index)
            {
                m_oldW = otherReplace->m_oldW;
                m_oldH = otherReplace->m_oldH;
                return true;
            }
        }
        return false;
    }
private:
    std::vector<DocumentItem> & m_items;
    size_t m_index;
    unsigned int m_oldW = 0;
    unsigned int m_oldH = 0;
    unsigned int m_newW = 0;
    unsigned int m_newH = 0;
};