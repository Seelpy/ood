#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
    double windSpeed = 0;
    double windDirection = 0;
};

std::string GetObserverType(
        const IObservable<SWeatherInfo> *in, const IObservable<SWeatherInfo> *out, const IObservable<SWeatherInfo> *obs)
{
    std::string location = "unknown";
    if (obs == in)
    {
        location = "inside";
    }
    else if (obs == out)
    {
        location = "outside";
    }
    return location;
}

class CSequenceStatistics
{
public:
    void Add(double value)
    {
        if (m_min > value)
        {
            m_min = value;
        }
        if (m_max < value)
        {
            m_max = value;
        }

        m_sum += value;
        m_sequenceCount++;
    }

    void Write(const std::string &sequenceName) const
    {
        std::cout << "Max " << sequenceName << " " << m_max << std::endl;
        std::cout << "Min " << sequenceName << " " << m_min << std::endl;
        std::cout << "Average " << sequenceName << " " << (m_sum / m_sequenceCount) << std::endl;
        std::cout << "----------------" << std::endl;
    }

private:
    double m_min = std::numeric_limits<double>::infinity();
    double m_max = -std::numeric_limits<double>::infinity();
    double m_sum = 0;
    int m_sequenceCount = 0;
};

class CSequenceWindStatistics
{
public:
    void Add(double speed, double direction)
    {
        m_speedStatistics.Add(speed);

        double radianDirection = direction * M_PI / 180.0;

        double x = speed * cos(radianDirection);
        double y = speed * sin(radianDirection);

        m_sumX += x;
        m_sumY += y;
    }

    void Write() const
    {
        std::cout << "Average Wind Degrees " << GetAverageDirection() << std::endl;
        m_speedStatistics.Write("Wind Speed");
    }

private:
    double GetAverageDirection() const
    {
        double averageDirection = atan2(m_sumY , m_sumX) * 180.0 / M_PI;
        return fmod(averageDirection + 360.0, 360.0);
    }

private:
    double m_sumX = 0;
    double m_sumY = 0;
    CSequenceStatistics m_speedStatistics;
};


class CDisplay : public IObserver<SWeatherInfo>
{
public:
    CDisplay(
            CObservable<SWeatherInfo> *m_weatherDataIn,
            CObservable<SWeatherInfo> *m_weatherDataOut) :
            m_weatherDataIn(m_weatherDataIn), m_weatherDataOut(m_weatherDataOut)
    {}

private:

    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
        Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
        остается публичным
    */
    void Update(SWeatherInfo const &data, const IObservable<SWeatherInfo> *observable) override
    {
        std::cout << "Current Location " << GetObserverType(m_weatherDataIn, m_weatherDataOut, observable) << std::endl;
        std::cout << "Current Temp " << data.temperature << std::endl;
        std::cout << "Current Hum " << data.humidity << std::endl;
        std::cout << "Current Pressure " << data.pressure << std::endl;
        std::cout << "----------------" << std::endl;
    }

    const IObservable<SWeatherInfo> *m_weatherDataIn;
    const IObservable<SWeatherInfo> *m_weatherDataOut;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
    CStatsDisplay(
            CObservable<SWeatherInfo> *m_weatherDataIn,
            CObservable<SWeatherInfo> *m_weatherDataOut) :
            m_weatherDataIn(m_weatherDataIn), m_weatherDataOut(m_weatherDataOut)
    {}

private:

    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
    Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
    остается публичным
    */
    void Update(SWeatherInfo const &data, const IObservable<SWeatherInfo> *observable) override
    {
        std::cout << "Current Location " << GetObserverType(m_weatherDataIn, m_weatherDataOut, observable) << std::endl;
        m_statisticsTemperature.Add(data.temperature);
        m_statisticsHumidity.Add(data.humidity);
        m_statisticsPressure.Add(data.pressure);
        m_statisticsWind.Add(data.windSpeed, data.windDirection);

        m_statisticsTemperature.Write("Temp");
        m_statisticsHumidity.Write("Hum");
        m_statisticsPressure.Write("Pressure");
        m_statisticsWind.Write();
    }

    CSequenceStatistics m_statisticsTemperature;
    CSequenceStatistics m_statisticsHumidity;
    CSequenceStatistics m_statisticsPressure;
    CSequenceWindStatistics m_statisticsWind;

    const IObservable<SWeatherInfo> *m_weatherDataIn;
    const IObservable<SWeatherInfo> *m_weatherDataOut;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
    // Температура в градусах Цельсия
    double GetTemperature() const
    {
        return m_temperature;
    }

    // Относительная влажность (0...100)
    double GetHumidity() const
    {
        return m_humidity;
    }

    // Атмосферное давление (в мм.рт.ст)
    double GetPressure() const
    {
        return m_pressure;
    }

    double GetWindSpeed() const
    {
        return m_windSpeed;
    }

    double GetWindDirection() const
    {
        return m_windDirection;
    }

    void MeasurementsChanged()
    {
        NotifyObservers();
    }

    void SetMeasurements(double temp, double humidity, double pressure, double windSpeed = 0, double windDirection = 0)
    {
        m_humidity = humidity;
        m_temperature = temp;
        m_pressure = pressure;
        m_windSpeed = windSpeed;
        m_windDirection = windDirection;

        MeasurementsChanged();
    }

protected:
    SWeatherInfo GetChangedData() const override
    {
        SWeatherInfo info;
        info.temperature = GetTemperature();
        info.humidity = GetHumidity();
        info.pressure = GetPressure();
        info.windSpeed = GetWindSpeed();
        info.windDirection = GetWindDirection();
        return info;
    }

private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
    double m_windSpeed = 0.0;
    double m_windDirection = 0.0;
};
