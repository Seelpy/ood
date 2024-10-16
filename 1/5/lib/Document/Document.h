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
#include "./Commands/ListCommand.h"
#include "./Commands/ReplaceTextCommand.h"
#include "./Commands/ResizeImageCommand.h"
#include "./Commands/SetTitleCommand.h"
#include "./HTML/utils.h"
#include <fstream>

class Document : public IDocument
{
public:
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
        AddAndExecuteCommand(std::make_shared<InsertImageCommand>(m_documentItems, position, path, w, h));
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

    void Save(const std::string &path) const override
    {
        std::ofstream outFile(path);
        if (!outFile)
        {
            throw std::logic_error("cant open file");
        }
        auto consts = GetConstItems();
        outFile << FormatDocumentToHTML(m_title, consts);
        outFile.close();
    }

    void List() override
    {
        auto consts = GetConstItems();
        AddAndExecuteCommand(std::make_shared<ListCommand>(m_title, consts));
    }

private:
    void AddAndExecuteCommand(const undo::IUndoableEditPtr& command)
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

    std::string m_title;
    undo::UndoManager m_stateManager;
    std::vector<DocumentItem> m_documentItems;
};