#include "../lib/WeatherData.h"

int main()
{
    CWeatherData wdIn;
    CWeatherData wdOut;

    CFishermanDisplay display;
    wdIn.RegisterObserver(display, EventType::Humidity, 5);
    wdOut.RegisterObserver(display, EventType::Humidity, 5);

    wdIn.SetMeasurements(25, 0.4, 760);
    wdOut.SetMeasurements(4, 0.8, 760);

    wdIn.SetMeasurements(10, 0.8, 761);
    wdOut.SetMeasurements(-10, 0.8, 761);

    return 0;
}
