#include "EventQueue.h"
#include "Event.h"

#include <vector>
#include <any>

dae::EventQueue::EventQueue()
    : m_Listeners{}
{
}

void dae::EventQueue::AddListener(const std::string& eventName, std::function<void(const Event&)> function)
{
    for (auto& [name, listener] : m_Listeners)
    {
        // if event already exists, add the listener to that event
        if (name == eventName)
        {
            listener.push_back(function);
            return;
        }
    }

    // if there is no event, add a new event with the listener
    m_Listeners[eventName] = { function };
}


void dae::EventQueue::RemoveListener(const std::string& eventName, std::function<void(const Event&)> function)
{
    auto it = m_Listeners.find(eventName);
    if (it != m_Listeners.end())
    {
        auto& listeners = it->second;
        listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
            [&function](const std::function<void(const Event&)>& f) { return f.target<void(const Event&)>() == function.target<void(const Event&)>(); }),
            listeners.end());
    }
}


void dae::EventQueue::Dispatch(const Event& event)
{
    const auto& eventName = event.name;
    if (m_Listeners.find(eventName) == m_Listeners.end()) return; // event doesn't exist

    for (const auto& listener : m_Listeners[eventName]) // triggers all listeners for that event
    {
        listener(event);
    }
}