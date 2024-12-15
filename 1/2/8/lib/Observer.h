#pragma once

#include <boost/signals2.hpp>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

enum class EventType
{
    Temperature,
    Pressure,
    Humidity,
};

// Template interface for observers
template<typename T>
class IObserver
{
public:
    virtual void Update(T const &data, EventType eventType) = 0;

    virtual ~IObserver() = default;
};

template<typename T>
class IObservable
{
public:
    virtual ~IObservable() = default;

    virtual void RegisterObserver(IObserver<T> &observer, EventType eventType) = 0;

    virtual void RemoveObserver(IObserver<T> &observer, EventType eventType) = 0;

protected:
    virtual void NotifyObservers(EventType eventType, const T &data) = 0;
};

template<class T>
class CObservable : public IObservable<T>
{
public:
    using ObserverType = IObserver<T>;

    void RegisterObserver(ObserverType &observer, EventType eventType) override
    {
        auto &signal = m_signals[eventType];
        auto conn = signal.connect(
                [&observer](const T &data, EventType type) {
                    observer.Update(data, type);
                });
        m_connections[eventType].emplace_back(&observer, conn);
    }

    void RemoveObserver(ObserverType &observer, EventType eventType) override
    {
        auto it = m_connections.find(eventType);
        if (it == m_connections.end())
        {
            return;
        }
        auto &connections = it->second;
        for (auto connIt = connections.begin(); connIt != connections.end();)
        {
            if (connIt->first == &observer)
            {
                if (connIt->second.connected())
                {
                    connIt->second.disconnect();
                }
                connIt = connections.erase(connIt);
                return;
            }
            else
            {
                ++connIt;
            }
        }
    }

protected:
    void NotifyObservers(EventType eventType)
    {
        T data = GetChangedData();
        NotifyObservers(eventType, data);
    }

    void NotifyObservers(EventType eventType, const T &data) override
    {
        m_signals[eventType](data, eventType);
    }

    virtual T GetChangedData() const = 0;

private:
    std::map<EventType, boost::signals2::signal<void(const T &, EventType eventType)>> m_signals;
    std::map<EventType, std::vector<std::pair<IObserver<T> *, boost::signals2::connection>>> m_connections;
};