#pragma once

#include <sstream>
#include "./../Menu/Menu.h"
#include "./../Document/IDocument.h"
#include <iostream>

class CommandHandler
{
public:
    CommandHandler(Menu &menu, IDocument &document)
            : m_menu(menu), m_document(document)
    {
        m_menu.AddItem("h", "Help", [this](std::istream &) { m_menu.ShowInstructions(); });
        AddMenuItem("ip", "Insert paragraph", &CommandHandler::InsertParagraph);
        AddMenuItem("ii", "Insert image", &CommandHandler::InsertImage);
        AddMenuItem("l", "Show document", &CommandHandler::List);
        AddMenuItem("st", "Set title", &CommandHandler::SetTitle);
        AddMenuItem("rt", "Replace text", &CommandHandler::ReplaceText);
        AddMenuItem("rs", "Resize image", &CommandHandler::ResizeImage);
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

    double GetDouble(std::istream &in)
    {
        double data;
        in >> data;
        return data;
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

    std::string GetText(std::istream &in)
    {
        std::string text;
        getline(in, text);
        return text;
    }

    void AddMenuItem(const std::string &shortcut, const std::string &description, MenuHandler handler)
    {
        m_menu.AddItem(shortcut, description, bind(handler, this, std::placeholders::_1));
    }

    void List(std::istream &)
    {
        auto items = m_document.List();
        auto title = m_document.GetTitle();
        std::cout << "Title: " << title << std::endl;
        int i = 0;
        for (auto item: items)
        {
            std::cout << i << ". ";
            if (auto image = item.GetImage(); image != nullptr)
            {
                std::cout << "Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath();
            }
            if (auto paragraph = item.GetParagraph(); paragraph != nullptr)
            {
                std::cout << "Paragraph: " << paragraph->GetText();
            }
            std::cout << std::endl;
            i++;
        }
    }

    void InsertParagraph(std::istream &in)
    {
        auto pos = GetOptionalPosition(in);
        auto text = GetText(in);
        m_document.InsertParagraph(text, pos);
    }

    void InsertImage(std::istream &in)
    {
        auto pos = GetOptionalPosition(in);
        auto path = GetString(in);
        auto w = GetDouble(in);
        auto h = GetDouble(in);
        m_document.InsertImage(path, w, h, pos);
    }

    void SetTitle(std::istream &in)
    {
        m_document.SetTitle(GetText(in));
    }

    void ReplaceText(std::istream &in)
    {
        auto pos = GetPosition(in);
        auto text = GetText(in);
        m_document.ReplaceText(text, pos);
    }

    void ResizeImage(std::istream &in)
    {
        auto pos = GetPosition(in);
        auto w = GetDouble(in);
        auto h = GetDouble(in);
        m_document.ResizeImage(pos, w, h);
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