#pragma once

#include <utility>
#include "ConstDocumentItem.h"
#include "Image/IImage.h"
#include "Paragraph/IParagraph.h"
#include "Paragraph/Paragraph.h"

class DocumentItem : public ConstDocumentItem
{
public:
    explicit DocumentItem (std::shared_ptr<IImage> image) : ConstDocumentItem(image), m_image(std::move(image)) {}

    explicit DocumentItem (std::shared_ptr<IParagraph> paragraph) : ConstDocumentItem(paragraph), m_paragraph(std::move(paragraph)) {}

    std::shared_ptr<IImage> GetImage()
    {
        return m_image;
    }

    std::shared_ptr<IParagraph> GetParagraph()
    {
        return m_paragraph;
    }

private:
    std::shared_ptr<IImage> m_image;
    std::shared_ptr<IParagraph> m_paragraph;
};