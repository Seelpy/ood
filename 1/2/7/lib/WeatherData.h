﻿#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include "Observer.h"

struct SWeatherInfo
{
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
};

class CFishermanDisplay : public IObserver<SWeatherInfo>
{
private:
    void Update(SWeatherInfo const& data, EventType eventType)
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

class CWeatherData;

class CWeatherData : public CObservable<SWeatherInfo>
{
public:

    double GetTemperature()const
    {
        return m_temperature;
    }

    double GetHumidity()const
    {
        return m_humidity;
    }

    double GetPressure()const
    {
        return m_pressure;
    }

    double GetWindSpeed()const
    {
        return m_windSpeed;
    }

    double GetWindDirection()const
    {
        return m_windDirection;
    }

    void MeasurementsChanged(EventType eventType)
    {
        NotifyObservers(eventType);
    }

    void SetTemp(double temp)
    {
        m_temperature = temp;

        MeasurementsChanged(EventType::Temperature);
    }

    void SetHumidity(double humidity)
    {
        m_humidity = humidity;

        MeasurementsChanged(EventType::Humidity);
    }

    void SetPressure(double pressure)
    {
        m_pressure = pressure;

        MeasurementsChanged(EventType::Pressure);
    }

    void SetMeasurements(double temp, double humidity, double pressure)
    {
        m_humidity = humidity;
        m_temperature = temp;
        m_pressure = pressure;

        MeasurementsChanged(EventType::Temperature);
        MeasurementsChanged(EventType::Pressure);
        MeasurementsChanged(EventType::Humidity);
    }

protected:
    SWeatherInfo GetChangedData()const override
    {
        SWeatherInfo info;
        info.temperature = GetTemperature();
        info.humidity = GetHumidity();
        info.pressure = GetPressure();
        return info;
    }
private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
    double m_windSpeed = 0.0;
    double m_windDirection = 0.0;
};