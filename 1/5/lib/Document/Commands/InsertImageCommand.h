#pragma once

#include "./../../Command/AbstractUndoableEdit.h"
#include "./../DocumentItem.h"
#include <utility>
#include <vector>
#include <optional>
#include "./../Image/Image.h"
#include "InsertDocumentItemCommand.h"

class InsertImageCommand : public InsertDocumentItemCommand
{
public:
    InsertImageCommand(
            std::vector<DocumentItem> &items,
            std::optional<size_t> index,
            std::string imagePath,
            unsigned int w,
            unsigned int h
    ) : InsertDocumentItemCommand(
            items, index, DocumentItem(std::make_shared<Image>(imagePath, w, h)))
    {
    }
};