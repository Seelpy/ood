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
	Duck(FlyStrategy flyBehavior,
		QuackStrategy quackBehavior,
		DanceStrategy danceBehavior)
		: m_quackBehavior(std::move(quackBehavior)), m_danceBehavior(std::move(danceBehavior))
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		SetFlyBehavior(flyBehavior);
	}

	void Quack() const
	{
        m_quackBehavior();
	}

	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
        m_flyBehavior();
	}

	virtual void Dance()
	{
        m_danceBehavior();
	}

	void SetFlyBehavior(FlyStrategy flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = std::move(flyBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyStrategy m_flyBehavior;
	QuackStrategy m_quackBehavior;
	DanceStrategy m_danceBehavior;
};

#endif
