#include <gtest/gtest.h>
#include <istream>
#include "../lib/Observer.h"
#include "../lib/WeatherData.h"

class ObserverWithSelfRemoving : public IObserver<SWeatherInfo>
{
public:
    explicit ObserverWithSelfRemoving(CObservable<SWeatherInfo> &observable) : m_observable(observable)
    {
    }

    void Update(SWeatherInfo const &data) override
    {
        m_observable.RemoveObserver(*this);
    }

private:
    CObservable<SWeatherInfo> &m_observable;
};

TEST(observer_test2, removing_observer_success)
{
    CWeatherData wd;

    CDisplay display1;
    wd.RegisterObserver(display1);
    ObserverWithSelfRemoving selfRemovingObserver(wd);

    wd.RegisterObserver(selfRemovingObserver);

    wd.SetMeasurements(1, 1, 1);

    wd.SetMeasurements(2, 2, 2);
}


GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}