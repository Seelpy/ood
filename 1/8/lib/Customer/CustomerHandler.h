#pragma once

#include <sstream>
#include "./../Menu/Menu.h"
#include "./../Gumball/GumballMachine.h"
#include <iostream>

class CommandHandler // TODO: для мульти
{
public:
    CommandHandler(Menu &menu, GumballMachine &machine)
            : m_menu(menu), m_machine(machine)
    {
        m_menu.AddItem("h", "Help", [this](std::istream &) { m_menu.ShowInstructions(); });
        AddMenuItem("ac", "Add coin", &CommandHandler::AddCount);
        AddMenuItem("ta", "Take away coin", &CommandHandler::TakeAwayCoin);
        AddMenuItem("tc", "Take Crank", &CommandHandler::TurnCrank);
        AddMenuItem("pa", "Pick up gumball", &CommandHandler::TakeAwayCoin);
        AddMenuItem("i", "Info about machine", &CommandHandler::ToString);
    }

private:
    Menu &m_menu;
    GumballMachine &m_machine;

    typedef void (CommandHandler::*MenuHandler)(std::istream &in);

    void AddMenuItem(const std::string &shortcut, const std::string &description, MenuHandler handler)
    {
        m_menu.AddItem(shortcut, description, bind(handler, this, std::placeholders::_1));
    }

    void AddCount(std::istream &in)
    {
        m_machine.InsertQuarter();
    }

    void TakeAwayCoin(std::istream &in)
    {
        m_machine.EjectQuarter();
    }

    void TurnCrank(std::istream &in)
    {
        m_machine.TurnCrank();
    }

    void ToString(std::istream &in)
    {
        std::cout << m_machine.ToString() << std::endl;
    }
};