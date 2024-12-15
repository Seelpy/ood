#pragma once

#include "IDocument.h"

#include <vector>
#include "IDocument.h"
#include "DocumentItem.h"
#include "./../Command/UndoManager.h"
#include "./Commands/DeleteItemCommand.h"
#include "./Commands/InsertDocumentItemCommand.h"
#include "./Commands/InsertImageCommand.h"
#include "./Commands/InsertParagraphCommand.h"
#include "./Commands/ReplaceTextCommand.h"
#include "./Commands/ResizeImageCommand.h"
#include "./Commands/SetTitleCommand.h"
#include "./HTML/utils.h"
#include <fstream>
#include "./Util/FileCopy.h"
#include "exception"

const std::string IMAGE_DIR = "./images/";

class Document : public IDocument
{
public:
    ~Document()
    {
        ClearImagesIfNeed();
    }

    void InsertParagraph(
            const std::string &text,
            std::optional<size_t> position = std::nullopt) override
    {
        AddAndExecuteCommand(std::make_shared<InsertParagraphCommand>(m_documentItems, position, text));
    }

    void ReplaceText(const std::string &newText, size_t index) override
    {

        AddAndExecuteCommand(std::make_shared<ReplaceTextCommand>(m_documentItems, index, newText));
    }

    void ResizeImage(size_t index, unsigned int w, unsigned int h) override
    {

        AddAndExecuteCommand(std::make_shared<ResizeImageCommand>(m_documentItems, index, w, h));
    }

    void InsertImage(
            const std::string &path, int w, int h,
            std::optional<size_t> position = std::nullopt) override
    {
        auto copyImagePath = CopyFile(path, IMAGE_DIR);
        try
        {
            AddAndExecuteCommand(std::make_shared<InsertImageCommand>(m_documentItems, position, copyImagePath, w, h));
        } catch (const std::invalid_argument& e)
        {
            if (std::filesystem::exists(copyImagePath))
            {
                std::filesystem::remove(copyImagePath);
            }
            throw  e;
        }
    }

    [[nodiscard]] size_t GetItemsCount() const override
    {
        return m_documentItems.size();
    }

    [[nodiscard]] ConstDocumentItem GetItem(size_t index) const override
    {
        return m_documentItems.at(index);
    }

    DocumentItem GetItem(size_t index) override
    {
        return m_documentItems.at(index);
    }

    void DeleteItem(size_t index) override
    {
        AddAndExecuteCommand(std::make_shared<DeleteItemCommand>(m_documentItems, index));
    }

    [[nodiscard]] std::string GetTitle() const override
    {
        return m_title;
    }

    void SetTitle(const std::string &title) override
    {
        AddAndExecuteCommand(std::make_shared<SetTitleCommand>(m_title, title));
    }

    [[nodiscard]] bool CanUndo() const override
    {
        return m_stateManager.CanUndo();
    }

    void Undo() override
    {
        if (!CanUndo())
        {
            throw std::logic_error("cant undo");
        }
        m_stateManager.Undo();
    }

    [[nodiscard]] bool CanRedo() const override
    {
        return m_stateManager.CanRedo();
    }

    void Redo() override
    {
        if (!CanRedo())
        {
            throw std::logic_error("cant redo");
        }
        m_stateManager.Redo();
    }

    void Save(const std::string &path) override
    {
        std::ofstream outFile(path);
        if (!outFile)
        {
            throw std::logic_error("cant open file");
        }
        auto consts = GetConstItems();
        outFile << FormatDocumentToHTML(m_title, consts);
        outFile.close();
        m_isSaved = true;
    }

    std::vector<ConstDocumentItem> List() override
    {
        return GetConstItems();
    }

private:
    void AddAndExecuteCommand(const undo::IUndoableEditPtr &command)
    {
        m_stateManager.AddEdit(command);
        m_stateManager.Redo();
    }

    std::vector<ConstDocumentItem> GetConstItems() const
    {
        std::vector<ConstDocumentItem> constDocumentItems;
        constDocumentItems.reserve(m_documentItems.size());

        for (const auto &item: m_documentItems)
        {
            constDocumentItems.emplace_back(static_cast<const ConstDocumentItem &>(item));
        }

        return constDocumentItems;
    }

    void ClearImagesIfNeed()
    {
        if (m_isSaved)
        {
            return;
        }
        for (const auto& item :GetConstItems())
        {
            if (auto image = item.GetImage(); image != nullptr)
            {
                if (std::filesystem::exists(image->GetPath()))
                {
                    std::filesystem::remove(image->GetPath());
                }
            }
        }
    }

    std::string m_title;
    undo::UndoManager m_stateManager;
    std::vector<DocumentItem> m_documentItems;
    bool m_isSaved = false;
};