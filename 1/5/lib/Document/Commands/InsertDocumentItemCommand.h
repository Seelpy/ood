#pragma once

#include "./../../Command/AbstractUndoableEdit.h"
#include "./../DocumentItem.h"
#include <utility>
#include <vector>
#include <optional>
#include "./../Paragraph/Paragraph.h"

class InsertDocumentItemCommand : public undo::AbstractUndoableEdit
{
public:
    InsertDocumentItemCommand(std::vector<DocumentItem> &items, std::optional<size_t> index, DocumentItem item) :
            m_items(items), m_item(std::move(item)), m_index(index)
    {
    }

    void RedoImpl() override
    {
        if (!m_index.has_value())
        {
            m_items.insert(m_items.begin() + m_index.value(), 1, m_item);
        }
        else
        {
            m_items.insert(m_items.end(), 1, m_item);
        }
    }

    void UndoImpl() override
    {
        if (!m_index.has_value())
        {
            m_items.erase(m_items.begin() + m_index.value());
        }
        else
        {
            m_items.erase(m_items.end());
        }
    }

    bool ReplaceEditImpl(const undo::IUndoableEditPtr& edit)
    {
        if (auto otherInsert = std::dynamic_pointer_cast<InsertDocumentItemCommand>(edit); otherInsert && otherInsert->m_index == m_index)
        {

            return true;
        }
        return false;
    }

private:
    std::vector<DocumentItem> m_items;
    DocumentItem m_item;
    std::optional<size_t> m_index;
};