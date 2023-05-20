#pragma once

#include "Singleton.h"

#include <map>
#include <functional>
#include <string>


//#include <algorithm>

namespace dae
{
    struct Event;
    class EventQueue final : public Singleton<EventQueue>
    {
    public:

        EventQueue();
        ~EventQueue() = default;
        EventQueue(const EventQueue&) = delete;
        EventQueue(EventQueue&&) = delete;
        EventQueue& operator= (const EventQueue&) = delete;
        EventQueue& operator= (const EventQueue&&) = delete;

        void AddListener(const std::string& eventName, std::function<void(const Event&)> function);
        void RemoveListener(const std::string& eventName, std::function<void(const Event&)> function);
        void Dispatch(const Event& event);

    private:
        std::map<std::string, std::vector<std::function<void(const Event&)>>> m_Listeners;
    };
}