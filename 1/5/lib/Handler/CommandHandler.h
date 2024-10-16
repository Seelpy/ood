#pragma once

#include <sstream>
#include "./../Menu/Menu.h"
#include "./../Document/IDocument.h"

class CommandHandler
{
public:
    CommandHandler(Menu &menu, IDocument &document)
            : m_menu(menu), m_document(document)
    {
        m_menu.AddItem("h", "Help", [this](std::istream &) { m_menu.ShowInstructions(); });
        AddMenuItem("ip", "InsertParagraph", &CommandHandler::InsertParagraph);
        AddMenuItem("l", "Show document", &CommandHandler::List);
        AddMenuItem("st", "Set title", &CommandHandler::SetTitle);
        AddMenuItem("rt", "Replace text", &CommandHandler::ReplaceText);
        AddMenuItem("di", "Delete item", &CommandHandler::DeleteItem);
        AddMenuItem("u", "Undo command", &CommandHandler::Undo);
        AddMenuItem("r", "Redo undone command", &CommandHandler::Redo);
        AddMenuItem("s", "Save to html", &CommandHandler::Save);
    }

private:
    Menu &m_menu;
    IDocument &m_document;

    typedef void (CommandHandler::*MenuHandler)(std::istream &in);

    std::optional<size_t> GetOptionalPosition(std::istream &in)
    {
        std::string data;
        in >> data;
        if (data == "end")
        {
            return std::nullopt;
        }
        return std::stoi(data);
    }

    size_t GetPosition(std::istream &in)
    {
        size_t data;
        in >> data;
        return data;
    }

    std::string GetString(std::istream &in)
    {
        std::string data;
        in >> data;
        return data;
    }

    void AddMenuItem(const std::string &shortcut, const std::string &description, MenuHandler handler)
    {
        m_menu.AddItem(shortcut, description, bind(handler, this, std::placeholders::_1));
    }

    void List(std::istream &)
    {
        m_document.List();
    }

    void InsertParagraph(std::istream &in)
    {
        auto pos = GetOptionalPosition(in);
        auto text = GetString(in);
        m_document.InsertParagraph(text, pos);
    }

    void SetTitle(std::istream &in)
    {
        m_document.SetTitle(GetString(in));
    }

    void ReplaceText(std::istream &in)
    {
        auto pos = GetPosition(in);
        auto text = GetString(in);
        m_document.ReplaceText(text, pos);
    }

    void DeleteItem(std::istream &in)
    {
        m_document.DeleteItem(GetPosition(in));
    }

    void Undo(std::istream &)
    {
        if (m_document.CanUndo())
        {
            m_document.Undo();
        }
        else
        {
            std::cout << "Can't undo" << std::endl;
        }
    }

    void Redo(std::istream &)
    {
        if (m_document.CanRedo())
        {
            m_document.Redo();
        }
        else
        {
            std::cout << "Can't redo" << std::endl;
        }
    }

    void Save(std::istream &in)
    {
        m_document.Save(GetString(in));
    }
};