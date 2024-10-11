#include <gtest/gtest.h>
#include <istream>
#include "../lib/Observer.h"
#include "../lib/WeatherData.h"
#include <functional>
#include <utility>

class PriorityObserverChecker : public IObserver<SWeatherInfo>
{
public:
    PriorityObserverChecker(int callNumber, std::function<int()> getCallNumberFunc)
            : m_callNumber(callNumber), m_getCallNumberFunc(std::move(getCallNumberFunc))
    {
    }

    void Update(SWeatherInfo const& data) override
    {
        ASSERT_EQ(m_callNumber, m_getCallNumberFunc());
    }

private:
    int m_callNumber;
    std::function<int()> m_getCallNumberFunc;
};

TEST(observer_test3, priority_observer_success)
{
    CWeatherData wd;

    std::vector<int> callOrder;

    int callNumber = 1;
    int callCount = 0;

    auto callbackFunc = [&callNumber, &callCount](){
        callCount++;
        return callNumber++;
    };

    PriorityObserverChecker highPriority(1, callbackFunc);
    PriorityObserverChecker lowPriority(2, callbackFunc);
    PriorityObserverChecker lowerPriority(3, callbackFunc);

    wd.RegisterObserver(highPriority, 6);
    wd.RegisterObserver(lowPriority, 3);
    wd.RegisterObserver(lowerPriority, 1);

    wd.SetMeasurements(5, 1, 761);

    ASSERT_EQ(3, callCount);
}


GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}