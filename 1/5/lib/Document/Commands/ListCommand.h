#pragma once

#include "./../../Command/AbstractUndoableEdit.h"
#include "./../DocumentItem.h"
#include <utility>
#include <vector>
#include <optional>
#include "./../Paragraph/Paragraph.h"
#include "InsertDocumentItemCommand.h"
#include <iostream>

class ListCommand : public undo::AbstractUndoableEdit
{
public:
    ListCommand(
            std::string title,
            std::vector<ConstDocumentItem> &items
    ) : m_items(items), m_title(std::move(title))
    {
    }

    void RedoImpl() override
    {
        std::cout << "Title: " << m_title << std::endl;
        int i = 1;
        for (auto item: m_items)
        {
            std::cout << i << ". ";
            if (auto image = item.GetImage(); image != nullptr)
            {
                std::cout << "Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath();
                i++;
            }
            if (auto paragraph = item.GetParagraph(); paragraph != nullptr)
            {
                std::cout << "Paragraph: " << paragraph->GetText();
                i++;
            }
        }
    }

private:
    std::vector<ConstDocumentItem> m_items;
    std::string m_title;
};