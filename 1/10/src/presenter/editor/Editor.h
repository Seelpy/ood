#pragma once

#include "./../IPresenter.h"
#include "./../BasePresenter.h"
#include "./../menu/Menu.h"
#include "./../../model/draft/IDraft.h"
#include "./../../view/draft/Draft.h"
#include "./../../view/container/Container.h"
#include "./../shape/Shape.h"
#include "../../model/style/fill/FIllStyle.h"
#include "../../model/style/line/LineStyle.h"
#include <memory>

class EditorPresenter: public BasePresenter {
public:
    EditorPresenter(const IViewPtr& draft , const IViewPtr& menu): BasePresenter() {
        m_views = {menu, draft};
        m_editor = std::make_shared<ContainerView>(common::Rect{{0, 0}, {1000, 1000}}, m_views);
        InitBase(m_editor);
    }

    IViewPtr GetView() override
    {
        return m_editor;
    }

private:
    IViewPtr GetDraftView() {
    }

    IViewPtr GetMenuView() {

    }

    IViewPtr m_editor;
    std::vector<IViewPtr> m_views;
    std::shared_ptr<MenuPresenter> m_menu;
};