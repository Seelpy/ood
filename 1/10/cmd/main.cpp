#include "./../src/app/Editor.h"
#include <string>

int main()
{
    auto draft = std::make_shared<Draft>(common::Size{1000, 1000});
    draft->AddShape(std::make_shared<Shape>("circle", common::Rect{{100, 100}, {50, 50}}, std::make_shared<LineStyle>(102340, 1), std::make_shared<FillStyle>(34234)));
    draft->AddShape(std::make_shared<Shape>("circle", common::Rect{{150, 150}, {150, 50}}, std::make_shared<LineStyle>(2314, 1), std::make_shared<FillStyle>(234234)));

    Editor editor(draft);
    editor.Run();
}
