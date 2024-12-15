#pragma once

#include <string>
#include <vector>
#include "./../ConstDocumentItem.h"
#include <sstream>

std::string HtmlEncode(const std::string &text)
{
    std::string encoded;
    for (char c : text)
    {
        switch (c)
        {
            case '<': encoded += "&lt;"; break;
            case '>': encoded += "&gt;"; break;
            case '"': encoded += "&quot;"; break;
            case '\'': encoded += "&apos;"; break;
            case '&': encoded += "&amp;"; break;
            default: encoded += c; break;
        }
    }
    return encoded;
}

std::string FormatDocumentItemToHTML(ConstDocumentItem item)
{
    if (auto image = item.GetImage(); image != nullptr)
    {
        return "<img src=\"" + image->GetPath() + "\" width=\"" + std::to_string(image->GetWidth()) +
               "\" height=\"" + std::to_string(image->GetHeight()) + "\" />";
    }
    if (auto paragraph = item.GetParagraph(); paragraph != nullptr)
    {
        return "<p>" + HtmlEncode(paragraph->GetText()) + "</p>";
    }
    return "";
}

std::string FormatDocumentToHTML(const std::string& title, const std::vector<ConstDocumentItem>& items)
{
    std::ostringstream result;
    result << "<!DOCTYPE html>" << std::endl
           << "<html lang=\"en\">" << std::endl
           << "<head>" << std::endl;
    result << "<title>" << title << "</title>" << std::endl;
    result << "</head>" << std::endl;
    result << "<body>" << std::endl;
    for (auto item: items)
    {
        result << FormatDocumentItemToHTML(item) << std::endl;
    }
    result << "</body>";
    result << "</html>";
    return result.str();
}
