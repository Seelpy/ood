#pragma once

#include "./../../Command/AbstractUndoableEdit.h"
#include "./../DocumentItem.h"
#include <utility>
#include <vector>
#include <optional>
#include "./../Paragraph/Paragraph.h"
#include "InsertDocumentItemCommand.h"

class DeleteItemCommand : public undo::AbstractUndoableEdit
{
public:
    DeleteItemCommand(std::vector<DocumentItem> &items, size_t index) :
            m_items(items), m_index(index)
    {
    }

    void RedoImpl() override
    {
        if (m_index >= m_items.size())
        {
            throw std::invalid_argument("Out of range by position");
        }

        m_removedItem = m_items.at(m_index);
        m_items.erase(m_items.begin() + m_index);
    }

    void UndoImpl() override
    {
        if (m_removedItem.has_value())
        {
            m_items.insert(m_items.begin() + m_index, 1, m_removedItem.value());
        }
    }

    bool ReplaceEditImpl(const undo::IUndoableEditPtr &edit) override
    {
        if (auto otherInsert = std::dynamic_pointer_cast<DeleteItemCommand>(edit);
                otherInsert && otherInsert->m_index == m_index)
        {
            return true;
        }
        return false;
    }

private:
    std::vector<DocumentItem>& m_items;
    size_t m_index;
    std::optional<DocumentItem> m_removedItem;
};