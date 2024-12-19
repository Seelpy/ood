#pragma once

#include "./../BasePresenter.h"
#include "./../../view/button/Button.h"
#include <functional>
#include <utility>
#include <string>


class ButtonPresenter: BasePresenter{
public:
    ButtonPresenter(common::Rect frame, const IFillStylePtr& fillStyle, const ILineStylePtr&  lineStyle, const std::string& text, std::function<void()> onMouseDownCallback): BasePresenter(), m_callback(std::move(onMouseDownCallback))
    {
        m_button = std::make_shared<ButtonView>(frame, fillStyle, lineStyle, text);
        InitBase(m_button);
    }

    IViewPtr GetView() override
    {
        return m_button;
    }

protected:
    void HandleMouseDownImpl(const common::Point &p) override
    {
        m_callback();
    }


private:
    std::function<void()> m_callback;
    std::shared_ptr<ButtonView> m_button;
};