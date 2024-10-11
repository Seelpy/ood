#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <istream>
#include "../lib/Observer.h"
#include "../lib/WeatherData.h"
#include <functional>
#include <utility>

class MockDisplay : public IObserver<SWeatherInfo>
{
public:
    MOCK_METHOD(void, Update, (const SWeatherInfo& data, const IObservable<SWeatherInfo>* observable), (override));

    MockDisplay() = default;
};

TEST(observer_test4, duo_observable_success)
{
    CWeatherData weatherDataIn;
    CWeatherData weatherDataOut;
    MockDisplay mockDisplay;

    weatherDataIn.RegisterObserver(mockDisplay, 1);
    weatherDataOut.RegisterObserver(mockDisplay, 2);

    SWeatherInfo dataIn = {1, 2, 3};
    SWeatherInfo dataOut = {4, 5, 6};

    EXPECT_CALL(mockDisplay, Update(testing::_, &weatherDataIn)).Times(1);
    EXPECT_CALL(mockDisplay, Update(testing::_, &weatherDataOut)).Times(1);

    weatherDataIn.SetMeasurements(dataIn.temperature, dataIn.humidity, dataIn.pressure);
    weatherDataOut.SetMeasurements(dataOut.temperature, dataOut.humidity, dataOut.pressure);
}


GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}