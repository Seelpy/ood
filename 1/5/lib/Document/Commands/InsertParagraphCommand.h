#pragma once

#include "./../../Command/AbstractUndoableEdit.h"
#include "./../DocumentItem.h"
#include <utility>
#include <vector>
#include <optional>
#include "./../Paragraph/Paragraph.h"
#include "InsertDocumentItemCommand.h"

class InsertParagraphCommand : public InsertDocumentItemCommand
{
public:
    InsertParagraphCommand(
            std::vector<DocumentItem> &items,
            std::optional<size_t> index,
            const std::string &text
    ) : InsertDocumentItemCommand(
            items, index, DocumentItem(std::make_shared<Paragraph>(text)))
    {
    }
};