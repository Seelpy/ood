#ifndef DUCK_H
#define DUCK_H

#include "Fly/IFlyBehavior.h"
#include "Quack/IQuakBehavior.h"
#include "Dance/IDanceBehavior.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

class Duck
{
public:
    Duck(
            std::unique_ptr<IFlyBehavior> &&flyBehavior,
            std::unique_ptr<IQuackBehavior> &&quackBehavior,
            std::unique_ptr<IDanceBehavior> &&danceBehavior)
            : m_quackBehavior(std::move(quackBehavior)), m_danceBehavior(std::move(danceBehavior))
    {
        assert(m_quackBehavior);
        SetFlyBehavior(std::move(flyBehavior));
    }

    void Quack() const
    {
        m_quackBehavior->Quack();
    }

    void Swim()
    {
        std::cout << "I'm swimming" << std::endl;
    }

    void Fly()
    {
        m_flyBehavior->Fly();
    }

    void SetFlyBehavior(std::unique_ptr<IFlyBehavior> &&flyBehavior)
    {
        assert(flyBehavior);
        m_flyBehavior = std::move(flyBehavior);
    }

    void Dance()
    {
        m_danceBehavior->Dance();
    }

    virtual void Display() const = 0;

    virtual ~Duck() = default;

private:
    std::unique_ptr<IFlyBehavior> m_flyBehavior;
    std::unique_ptr<IQuackBehavior> m_quackBehavior;
    std::unique_ptr<IDanceBehavior> m_danceBehavior;
};

#endif
