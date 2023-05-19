#include "EventQueue.h"
#include "Event.h"

#include <vector>



#include <any>

dae::EventQueue::EventQueue()
    : m_Listeners{}
{
}

void dae::EventQueue::AddListener(const std::string& eventName, std::function<void(const Event&)> listener)
{

    for (auto& [name, listeners] : m_Listeners) // [key,value]
    {
        // if event already exist add listener to that event
        if (name == eventName)
        {
            listeners.push_back(listener);
            return;
        }
    }
    // if there is no event, add new event with a listener
    m_Listeners[eventName] = { listener };

}

void dae::EventQueue::RemoveListener(const std::string& eventName, std::function<void(const Event&)> listener)
{
    auto it = m_Listeners.find(eventName);
    if (it != m_Listeners.end())
    {
        auto& listeners = it->second;
        listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
            [&listener](const std::function<void(const Event&)>& f) { return f.target<void(const Event&)>() == listener.target<void(const Event&)>(); }),
            listeners.end());
    }
}


void dae::EventQueue::Dispatch(const Event& event)
{
    const auto& eventName = event.name;
    if (m_Listeners.find(eventName) == m_Listeners.end()) return;

    for (const auto& listener : m_Listeners[eventName])
    {
        listener(event);
    }
}