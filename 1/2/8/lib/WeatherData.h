#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <boost/signals2.hpp>
#include "Observer.h"

struct SWeatherInfo
{
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
    using WeatherSignal = boost::signals2::signal<void(const SWeatherInfo &, EventType)>;

    [[nodiscard]] double GetTemperature() const
    {
        return m_temperature;
    }

    [[nodiscard]] double GetHumidity() const
    {
        return m_humidity;
    }

    [[nodiscard]] double GetPressure() const
    {
        return m_pressure;
    }

    void SetTemp(double temp)
    {
        m_temperature = temp;
        NotifyObservers(EventType::Temperature);
    }

    void SetHumidity(double humidity)
    {
        m_humidity = humidity;
        NotifyObservers(EventType::Humidity);
    }

    void SetPressure(double pressure)
    {
        m_pressure = pressure;
        NotifyObservers(EventType::Pressure);
    }

    void SetMeasurements(double temp, double humidity, double pressure)
    {
        m_temperature = temp;
        m_humidity = humidity;
        m_pressure = pressure;

        NotifyObservers(EventType::Temperature);
        NotifyObservers(EventType::Humidity);
        NotifyObservers(EventType::Pressure);
    }

private:
    SWeatherInfo GetChangedData() const
    {
        return {m_temperature, m_humidity, m_pressure};
    }

private:
    WeatherSignal m_signal;
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
};

class CFishermanDisplay : public IObserver<SWeatherInfo>
{

private:
    void Update(const SWeatherInfo &data, EventType eventType)
    {
        if (eventType == EventType::Temperature)
        {
            std::cout << "Current Temperature: " << data.temperature << std::endl;
        }
        else if (eventType == EventType::Pressure)
        {
            std::cout << "Current Pressure: " << data.pressure << std::endl;
        }

        std::cout << "Current Humidity: " << data.humidity << std::endl;
        std::cout << "----------------" << std::endl;
    }
};