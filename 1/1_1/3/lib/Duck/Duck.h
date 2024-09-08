#ifndef DUCK_H
#define DUCK_H

#include "Fly/FlyBehavior.h"
#include "Dance/DanceBehavior.h"
#include "Quack/QuakBehavior.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

class Duck
{
public:
	Duck(std::unique_ptr<FlyStrategy>&& flyBehavior,
		std::unique_ptr<QuackStrategy>&& quackBehavior,
		std::unique_ptr<DanceStrategy>&& danceBehavior)
		: m_quackBehavior(std::move(quackBehavior)), m_danceBehavior(std::move(danceBehavior))
	{
		assert(m_quackBehavior);
		SetFlyBehavior(std::move(flyBehavior));
	}

	void Quack() const
	{
        (*m_quackBehavior)();
	}

	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
        (*m_flyBehavior)();
	}

	virtual void Dance()
	{
        (*m_danceBehavior)();
	}

	void SetFlyBehavior(std::unique_ptr<FlyStrategy>&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = std::move(flyBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	std::unique_ptr<FlyStrategy> m_flyBehavior;
	std::unique_ptr<QuackStrategy> m_quackBehavior;
	std::unique_ptr<DanceStrategy> m_danceBehavior;
};

#endif
