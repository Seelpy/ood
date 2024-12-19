#pragma once

#include "./../IPresenter.h"
#include "./../BasePresenter.h"
#include "./../button/Button.h"
#include "./../../model/draft/IDraft.h"
#include "./../../view//draft/Draft.h"
#include "./../../view/container/Container.h"
#include "./../shape/Shape.h"
#include <memory>

class MenuPresenter: public BasePresenter {
public:
    MenuPresenter(const std::vector<std::shared_ptr<ButtonPresenter>>& buttonPresenters): BasePresenter() {
        for (const auto& presenter: buttonPresenters)
        {
            auto view = presenter->GetView();
            m_views.push_back(view);
        }

        m_menu = std::make_shared<ContainerView>(common::Rect{{0, 0}, {0, 0}}, m_views);
        InitBase(m_menu);
    }

    IViewPtr GetView() override
    {
        return m_menu;
    }

private:
    IViewPtr m_menu;
    std::vector<IViewPtr> m_views;
};