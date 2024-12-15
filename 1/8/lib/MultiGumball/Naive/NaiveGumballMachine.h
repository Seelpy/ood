#pragma once

#include <iostream>
#include <sstream>

namespace multiNaive {
    class GumballMachine {
    public:
        enum class State {
            SoldOut,
            NoQuarter,
            HasQuarter,
            Sold,
        };

        GumballMachine(unsigned count)
                : m_gumballsCount(count), m_state(count > 0 ? State::NoQuarter : State::SoldOut)
        {}

        void InsertQuarter() {
            using namespace std;
            if (m_quarter >= MAX_QUARTER) {
                cout << "You can't insert another quarter\n";
                return;
            }
            switch (m_state) {
                case State::SoldOut:
                    cout << "You can't insert a quarter, the machine is sold out\n";
                    break;
                case State::NoQuarter:
                    cout << "You inserted a quarter\n";
                    m_quarter++;
                    if (m_quarter == 1)
                    {
                        m_state = State::HasQuarter;
                    }
                    break;
                case State::HasQuarter:
                    cout << "You inserted another quarter\n";
                    m_quarter++;
                    break;
                case State::Sold:
                    cout << "Please wait, we're already giving you a gumball\n";
                    break;
            }
        }

        void EjectQuarter() {
            using namespace std;
            if (m_quarter > 0) {
                cout << "Return "<< m_quarter <<" quarters\n";
                m_quarter = 0;
                m_state = State::NoQuarter;
            } else {
                cout << "You can't eject, you haven't inserted a quarter yet\n";
            }
        }

        void TurnCrank() {
            using namespace std;
            switch (m_state) {
                case State::SoldOut:
                    cout << "You turned but there's no gumballs\n";
                    break;
                case State::NoQuarter:
                    cout << "You turned but there's no quarter\n";
                    break;
                case State::HasQuarter:
                    cout << "You turned...\n";
                    Dispense();
                    break;
                case State::Sold:
                    cout << "Turning twice doesn't get you another gumball\n";
                    break;
            }
        }

        void Refill(unsigned numBalls)
        {
            using namespace std;
            switch (m_state) {
                case State::SoldOut:
                    m_gumballsCount = numBalls;
                    std::cout << "Added gumball\n";
                    if (m_gumballsCount > 0)
                    {
                        m_state = State::NoQuarter;
                    }
                    break;
                case State::NoQuarter:
                    m_gumballsCount = numBalls;
                    std::cout << "Added gumball\n";
                    break;
                case State::HasQuarter:
                    m_gumballsCount = numBalls;
                    std::cout << "Added gumball\n";
                    break;
                case State::Sold:
                    std::cout << "Not added gumball when giving giving you a gumball\n";
                    break;
            }

        }

        [[nodiscard]] std::string ToString() const {
            std::string state = (m_state == State::SoldOut)
                                ? "sold out"
                                : (m_state == State::NoQuarter) ? "waiting for quarter"
                                                                : (m_state == State::HasQuarter) ? "waiting for turn of crank"
                                                                                                 : "delivering a gumball";

            std::ostringstream oss;
            oss << R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: )" << m_gumballsCount << " gumball" << (m_gumballsCount != 1 ? "s" : "")
                << R"(
Machine is )" << state << "\n";
            return oss.str();
        }

    private:
        void Dispense() {
            using namespace std;
            if (m_gumballsCount > 0 && m_quarter > 0)
            {
                --m_gumballsCount;
                --m_quarter;

                cout << "A gumball comes rolling out the slot...\n";

                if (m_gumballsCount == 0) {
                    cout << "Oops, out of gumballs\n";
                    cout << "Return all quarters\n";
                    m_state = State::SoldOut;
                }
                else if (m_quarter == 0)
                {
                    m_state = State::NoQuarter;
                }
            }
            else if (m_gumballsCount == 0)
            {
                cout << "No gumball dispensed\n";
            }
            else if (m_quarter == 0)
            {
                cout << "You need to pay first\n";
            }
        }

        unsigned m_gumballsCount;
        unsigned m_quarter = 0;
        static constexpr unsigned MAX_QUARTER = 5;
        State m_state = State::SoldOut;
    };
}