#pragma once

#include <string>
#include <vector>
#include "./../ConstDocumentItem.h"
#include <sstream>

std::string FormatDocumentItemToHTML(ConstDocumentItem item)
{
    if (auto image = item.GetImage(); image != nullptr)
    {
        return "<img src=\"" + image->GetPath() + "\" width=\"" + std::to_string(image->GetWidth()) +
               "\" height=\"" + std::to_string(image->GetHeight()) + "\" />";
    }
    if (auto paragraph = item.GetParagraph(); paragraph != nullptr)
    {
        return "<p>" + paragraph->GetText() + "</p>";
    }
    return "";
}

std::string FormatDocumentToHTML(std::string title, std::vector<ConstDocumentItem> items)
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