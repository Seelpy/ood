#pragma once

#include <string>
#include "exception"
#include <memory>

namespace undo
{
    class IUndoableEdit;

    using IUndoableEditPtr = std::shared_ptr<IUndoableEdit>;

    class IUndoableEdit
    {
    public:
        virtual bool CanUndo() const = 0;
        virtual bool CanRedo() const = 0;

        virtual void Undo() = 0;
        virtual void Redo() = 0;
        virtual void Destroy() = 0;

        virtual bool AddEdit(const IUndoableEditPtr& edit) = 0;

        virtual bool ReplaceEdit(const IUndoableEditPtr& edit) = 0;

        virtual std::string GetName() const = 0;

        virtual ~IUndoableEdit() = default;
    };

}

