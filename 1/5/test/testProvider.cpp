#include <gtest/gtest.h>

#include <sstream>
#include "../lib/Document/Commands/InsertParagraphCommand.h"
#include "../lib/Document/Commands/ReplaceTextCommand.h"
#include "../lib/Document/Commands/DeleteItemCommand.h"
#include "../lib/Document/Commands/SetTitleCommand.h"
#include "../lib/Document/Commands/InsertImageCommand.h"
#include "../lib/Document/Commands/ResizeImageCommand.h"
#include "../lib/Document/IDocument.h"
#include "../lib/Menu/Menu.h"
#include "../lib/Document/Document.h"


TEST(document, change_title) {
    Document document;
    std::string  title = "test";
    ASSERT_EQ(document.GetTitle(), "");
    document.SetTitle(title);
    ASSERT_EQ(document.GetTitle(), title);
    document.Undo();
    ASSERT_EQ(document.GetTitle(), "");
    document.Redo();
    ASSERT_EQ(document.GetTitle(), title);
}

TEST(document, insert_paragraph) {
    Document document;
    std::string text = "text";
    ASSERT_EQ(document.GetItemsCount(), 0);
    document.InsertParagraph(text);
    ASSERT_EQ(document.GetItemsCount(), 1);
    ASSERT_EQ(document.GetItem(0).GetParagraph()->GetText(), text);
    document.Undo();
    ASSERT_EQ(document.GetItemsCount(), 0);
    document.Redo();
    ASSERT_EQ(document.GetItemsCount(), 1);
    ASSERT_EQ(document.GetItem(0).GetParagraph()->GetText(), text);
}

TEST(document, replace_text) {
    Document document;
    std::string text = "text";
    std::string tex2 = "text2";
    document.InsertParagraph(text);
    document.ReplaceText(tex2, 0);
    ASSERT_EQ(document.GetItemsCount(), 1);
    ASSERT_EQ(document.GetItem(0).GetParagraph()->GetText(), tex2);
    document.Undo();
    ASSERT_EQ(document.GetItemsCount(), 1);
    ASSERT_EQ(document.GetItem(0).GetParagraph()->GetText(), text);
    document.Redo();
    ASSERT_EQ(document.GetItemsCount(), 1);
    ASSERT_EQ(document.GetItem(0).GetParagraph()->GetText(), tex2);
}

TEST(document, insert_image) {
    Document document;
    std::string path = "./data/1.bmp";
    document.InsertImage(path, 1, 2);
    ASSERT_EQ(document.GetItemsCount(), 1);
    ASSERT_EQ(document.GetItem(0).GetImage()->GetWidth(), 1);
    ASSERT_EQ(document.GetItem(0).GetImage()->GetHeight(), 2);
    document.Undo();
    ASSERT_EQ(document.GetItemsCount(), 0);
    document.Redo();
    ASSERT_EQ(document.GetItemsCount(), 1);
    ASSERT_EQ(document.GetItem(0).GetImage()->GetWidth(), 1);
    ASSERT_EQ(document.GetItem(0).GetImage()->GetHeight(), 2);
}

TEST(document, failed_insert_image_by_size) {
    Document document;
    std::string path = "./data/1.bmp";
    ASSERT_THROW(document.InsertImage(path, 0, 100), std::invalid_argument);
    ASSERT_THROW(document.InsertImage(path, 100, 0), std::invalid_argument);
    ASSERT_THROW(document.InsertImage(path, 100000, 100), std::invalid_argument);
    ASSERT_THROW(document.InsertImage(path, 100, 100000), std::invalid_argument);
}

TEST(document, failed_insert_by_indsex) {
    Document document;
    std::string text = "text";
    ASSERT_EQ(document.GetItemsCount(), 0);
    ASSERT_THROW(document.InsertParagraph(text, 100), std::invalid_argument);
}

TEST(document, delete_item) {
    Document document;
    std::string text = "text";
    document.InsertParagraph(text);
    document.DeleteItem(0);
    ASSERT_EQ(document.GetItemsCount(), 0);
    document.Undo();
    ASSERT_EQ(document.GetItemsCount(), 1);
    ASSERT_EQ(document.GetItem(0).GetParagraph()->GetText(), text);
    document.Redo();
    ASSERT_EQ(document.GetItemsCount(), 0);
}

TEST(document, failed_delete_item) {
    Document document;
    std::string text = "text";
    document.InsertParagraph(text);
    ASSERT_THROW(document.DeleteItem(1), std::invalid_argument);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}