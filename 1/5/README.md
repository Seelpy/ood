classDiagram
IParagraph <|.. Paragraph
IImage <|.. Image

    ConstDocumentItem <|-- DocumentItem
    IDocument <|.. Document
    Document *-- UndoManager
    Document *-- Document
    DocumentItem *-- IImage
    DocumentItem *-- IParagraph

    Document o-- SetTitleCommand
    Document o-- ResizeImageCommand
    Document o-- ReplaceTextCommand
    Document o-- InsertImageCommand
    Document o-- InsertParagraphCommand

    
    Menu *-- Item
    Menu o-- Document

    CommandHandler o-- Document
    CommandHandler o-- Menu
    
    class CommandHandler {
        - m_menu Menu
        - m_document Document
        - AddMenuItem(shortcut string, description string)
        - List(in istream)
        - InsertParagraph(in istream)
        - SetTitle(in istream)
        - ReplaceText(in istream)
        - DeleteItem(in istream)
        - Undo(in istream)
        - Redo(in istream)
        - Save(in istream)
    }

    namespace DocumentNamepsace {
        class IDocument {
            + InsertParagraph(text string, position size_t)*
            + ReplaceText(text string, position size_t)*
            + InsertImage(path string, width int, height int, position size_t)* IImage
            + ResizeImage(width int, height int, position size_t)*
            + GetItemsCount()* size_t;
            + GetItem(index size_t)* ConstDocumentItem
            + GetItem(index size_t)* DocumentItem
            + DeleteItem(index size_t)*
            + GetTitle()* string
            + SetTitle(title string)*
            + CanUndo()* bool
            + Undo()*
            + CanRedo()* bool
            + Redo()*
            + Save(path string)*
        }
        class Document {
            + InsertParagraph(text string, position size_t)
            + ReplaceText(text string, position size_t)
            + InsertImage(path string, width int, height int, position size_t) IImage
            + ResizeImage(width int, height int, position size_t)
            + GetItemsCount() size_t;
            + GetItem(index size_t) ConstDocumentItem
            + DeleteItem(index size_t)
            + GetTitle() string
            + SetTitle(title string)
            + CanUndo() bool
            + Undo()
            + CanRedo() bool
            + Redo()
            + Save(path string)
            - m_title string
            - m_items vector(DocumentItem)
            - m_undoManager UndoManager
        }
        class IParagraph {
            + GetText()* string
            + SetText(text string)*
        }

        class Paragraph {
            + GetText() string
            + SetText(text string)
        }

        class IImage {
            + GetPath()* string
            + GetWidth()* int
            + GetHeight()* int
            + Resize(width int, height int)*
        }

        class Image {
            + GetPath() string
            + GetWidth() int
            + GetHeight() int
            + Resize(width int, height int)
        }

        class ConstDocumentItem {
            + GetImage() IImage
            + GetIParahraph() IParagraph
        }

        class DocumentItem {
            + GetImage() IImage
            + GetIParahraph() IParagraph
        }
    }
        
        

        Document *-- DocumentItem
        

    namespace MenuNamespace {
        class Menu {
            + AddItem(shortcut string, description string, command function void(&args istream))
            + Run()
            + ShowInstructions()
            + Exit()
            - ExecuteCommand(command string)
            - m_items vector(Item) 
            - m_exit bool
        }

        class Item {
            + shortcut string
            + description string
            + command ICommand
        }
    }
    

    namespace Undo{
        class IUndoableEdit {
            <<interface>>
            +bool CanUndo() const
            +bool CanRedo() const
            +void Undo()
            +void Redo()
            +void Destroy()
            +bool AddEdit(IUndoableEditPtr edit)
            +bool ReplaceEdit(IUndoableEditPtr edit)
            +std::string GetName() const
        }

        class IUndoableEdit {
            <<interface>>
            +bool CanUndo() const
            +bool CanRedo() const
            +void Undo()
            +void Redo()
            +void Destroy()
            +bool AddEdit(IUndoableEditPtr edit)
            +bool ReplaceEdit(IUndoableEditPtr edit)
            +std::string GetName() const
        }

        class AbstractUndoableEdit {
            +bool CanUndo() const
            +bool CanRedo() const
            +void Undo() final
            +void Redo() final
            +void Destroy() final
            +bool AddEdit(IUndoableEditPtr edit) final
            +bool ReplaceEdit(IUndoableEditPtr edit) final
            +std::string GetName() const override
            +void SetReplaceable(bool canBeReplaced)
            
            -m_executed:m_executed
            -m_isAlive:bool
            - m_canBeReplaced:bool
            -m_name: string

            <<protected>>
            #void UndoImpl()
            #void RedoImpl()
            #void DestroyImpl()
            #bool AddEditImpl(IUndoableEditPtr edit)
            #bool ReplaceEditImpl(IUndoableEditPtr edit)
            #bool IsExecuted() const
            #void SetExecuted(bool executed)
            #void SetName(const std::string &name)
        }
        class CompoundEdit {
            # m_edits: vector
            # m_inProgress: bool
            - m_hasCustomName: bool
            +CompoundEdit(const std::optional<std::string> &customName = std::nullopt)
            +~CompoundEdit()
            +bool CanUndo() const
            +bool CanRedo() const
            +std::string GetName() const
            +void End()
            +size_t GetEditCount() const
            +IUndoableEditPtr GetEdit(size_t index) const
            #void DestroyImpl() noexcept
            #void UndoImpl()
            #void RedoImpl()
            #bool AddEditImpl(const IUndoableEditPtr &edit)
            #void EndImpl()
            #void SetName(const std::string &name)
        }   
        class UndoManager {
            - m_indexOfNextAdd: size_t
            +bool CanUndo() const final
            +bool CanRedo() const final
            +size_t GetCurrentEditIndex() const
            +void Clear()
            -bool AddEditImpl(const IUndoableEditPtr &edit) final
            -void UndoImpl() final
            -void RedoImpl() final
            -void EndImpl() final
            -void SetExecuted(bool executed) final
            -void DestroyImpl() throw() final
            -IUndoableEditPtr GetEditToBeUndone() const
            -IUndoableEditPtr GetEditToBeRedone() const
            -void UndoTo(const IUndoableEditPtr &edit)
            -void RedoTo(const IUndoableEditPtr &edit)
            -void TrimEdits(size_t from, size_t to)
        }
    }
    AbstractUndoableEdit ..|> IUndoableEdit
    CompoundEdit --|> AbstractUndoableEdit
    UndoManager --|> CompoundEdit

    namespace DocumentCommands {
        class DeleteItemCommand {
            -m_items: vector
            -m_index: size_t
            -m_removedItem: DocumentItem
            -void RedoImpl() override
            -void UndoImpl() override
            -bool ReplaceEditImpl(const undo::IUndoableEditPtr &edit) override
        }
        class InsertDocumentItemCommand {
            
        }
        class InsertImageCommand {

        }
        class InsertParagraphCommand {

        }
        class ReplaceTextCommand {

        }
        class ResizeImageCommand {

        }
        class SetTitleCommand {

        }
        class InsertDocumentItemCommand {

        }
    }
    DeleteItemCommand --|> AbstractUndoableEdit
    InsertDocumentItemCommand --|> AbstractUndoableEdit
    InsertImageCommand --|> InsertDocumentItemCommand
    InsertParagraphCommand --|> InsertDocumentItemCommand
    ReplaceTextCommand --|> AbstractUndoableEdit
    ResizeImageCommand --|> AbstractUndoableEdit
    SetTitleCommand --|> AbstractUndoableEdit
