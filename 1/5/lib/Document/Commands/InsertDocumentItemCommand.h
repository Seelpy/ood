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
            m_items.push_back(m_item);
            return;
        }
        auto index = m_index.value();
        if (index > m_items.size())
        {
            throw std::invalid_argument("Out of range by position");
        }
        if (!m_items.empty())
        {
            m_items.insert(m_items.begin() + m_index.value(), 1, m_item);
            return;
        }
        m_items.push_back(m_item);
    }

    void UndoImpl() override
    {
        if (m_index.has_value())
        {
            m_items.erase(m_items.begin() + m_index.value());
        }
        else
        {
            m_items.erase(m_items.end() - 1);
        }
    }

    bool ReplaceEditImpl(const undo::IUndoableEditPtr& edit) override
    {
        if (auto otherInsert = std::dynamic_pointer_cast<InsertDocumentItemCommand>(edit); otherInsert && otherInsert->m_index == m_index)
        {
            return true;
        }
        return false;
    }

private:
    std::vector<DocumentItem> & m_items;
    DocumentItem m_item;
    std::optional<size_t> m_index;
};