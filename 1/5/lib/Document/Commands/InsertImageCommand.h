#pragma once

#include "./../DocumentItem.h"
#include <utility>
#include <vector>
#include <optional>
#include "./../Image/Image.h"
#include "InsertDocumentItemCommand.h"
#include <filesystem>

class InsertImageCommand : public InsertDocumentItemCommand
{
public:
    InsertImageCommand(
            std::vector<DocumentItem> &items,
            std::optional<size_t> index,
            const std::string& imagePath,
            unsigned int w,
            unsigned int h
    ) : InsertDocumentItemCommand(
            items, index, DocumentItem(std::make_shared<Image>(imagePath, w, h)))
    {
       m_path = imagePath;
    }

    void DestroyImpl() override
    {
        if (std::filesystem::exists(m_path))
        {
            std::filesystem::remove(m_path);
        }
    }
private:
    std::string m_path;
};