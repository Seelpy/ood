#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <optional>
#include "ConstDocumentItem.h"
#include "DocumentItem.h"

class IDocument
{
public:
    virtual void InsertParagraph(
            const std::string &text,
            std::optional<size_t> position = std::nullopt) = 0;

    virtual void ReplaceText(
            const std::string &newText,
            size_t index) = 0;

    virtual void ResizeImage(
            size_t index,
            unsigned int w, unsigned int h) = 0;

    virtual void InsertImage(
            const std::string &path, int width, int height,
            std::optional<size_t> position = std::nullopt) = 0;

    virtual size_t GetItemsCount() const = 0;

    virtual ConstDocumentItem GetItem(size_t index) const = 0;

    virtual DocumentItem GetItem(size_t index) = 0;

    virtual void DeleteItem(size_t index) = 0;

    virtual std::string GetTitle() const = 0;

    virtual void SetTitle(const std::string &title) = 0;

    virtual bool CanUndo() const = 0;

    virtual void Undo() = 0;

    virtual bool CanRedo() const = 0;

    virtual void Redo() = 0;

    virtual void Save(const std::string &path) const = 0;

    virtual void List() = 0;

    virtual ~IDocument() = default;
};