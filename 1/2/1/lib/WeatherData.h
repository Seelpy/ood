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
};

void WriteStats(const std::string &statsName, double max, double min, double average)
{
    std::cout << "Max " << statsName << " " << max << std::endl;
    std::cout << "Min " << statsName << " " << min << std::endl;
    std::cout << "Average " << statsName << " " << average << std::endl;
    std::cout << "----------------" << std::endl;
}

// TODO: Реализовать печать отдельно
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

    double GetMax() const
    {
        return m_max;
    }

    double GetMin() const
    {
        return m_min;
    }

    double GetAverage() const
    {
        return m_sum / m_sequenceCount;
    }

private:
    double m_min = std::numeric_limits<double>::infinity();
    double m_max = -std::numeric_limits<double>::infinity();
    double m_sum = 0;
    int m_sequenceCount = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
        Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
        остается публичным
    */
    void Update(SWeatherInfo const &data) override
    {
        std::cout << "Current Temp " << data.temperature << std::endl;
        std::cout << "Current Hum " << data.humidity << std::endl;
        std::cout << "Current Pressure " << data.pressure << std::endl;
        std::cout << "----------------" << std::endl;
    }
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
    Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
    остается публичным
    */
    void Update(SWeatherInfo const &data) override
    {
        m_statisticsTemperature.Add(data.temperature);
        m_statisticsHumidity.Add(data.humidity);
        m_statisticsPressure.Add(data.pressure);

        WriteStats("Temp", m_statisticsTemperature.GetMax(),  m_statisticsTemperature.GetMin(), m_statisticsTemperature.GetAverage());
        WriteStats("Hum", m_statisticsHumidity.GetMax(),  m_statisticsHumidity.GetMin(), m_statisticsHumidity.GetAverage());
        WriteStats("Pressure", m_statisticsPressure.GetMax(),  m_statisticsPressure.GetMin(), m_statisticsPressure.GetAverage());
    }

    CSequenceStatistics m_statisticsTemperature;
    CSequenceStatistics m_statisticsHumidity;
    CSequenceStatistics m_statisticsPressure;
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

    void MeasurementsChanged()
    {
        NotifyObservers();
    }

    void SetMeasurements(double temp, double humidity, double pressure)
    {
        m_humidity = humidity;
        m_temperature = temp;
        m_pressure = pressure;

        MeasurementsChanged();
    }

protected:
    SWeatherInfo GetChangedData() const override
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
};
