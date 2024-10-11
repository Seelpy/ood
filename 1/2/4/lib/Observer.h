#pragma once

#include <set>
#include <functional>
#include <unordered_set>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObservable;


template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, const IObservable<T>* observable) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, int priority) override
	{
        try {
            auto result = m_priorityToObservers.insert({priority, {}});
            result.first->second.insert(&observer);
            m_observerToPriority[&observer] = priority;
        }
	}

	void NotifyObservers() override
	{
        T data = GetChangedData();
        auto observersCopy = m_priorityToObservers;
        for (auto it = observersCopy.rbegin(); it != observersCopy.rend(); ++it)
        {
            for (auto& observer : it->second)
            {
                observer->Update(data, this);
            }
        }
	}

	void RemoveObserver(ObserverType & observer) override
	{
        auto it = m_observerToPriority.find(&observer);
        if (it != m_observerToPriority.end())
        {
            int priority = it->second;

            auto &observerSet = m_priorityToObservers[priority];
            observerSet.erase(&observer);

            if (observerSet.empty())
            {
                m_priorityToObservers.erase(priority);
            }

            m_observerToPriority.erase(it);
        }
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
    std::map<int, std::unordered_set<ObserverType *>> m_priorityToObservers;
    std::unordered_map<ObserverType*, int> m_observerToPriority;
};
