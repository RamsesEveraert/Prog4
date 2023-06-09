#pragma once

#include "Singleton.h"

#include <map>
#include <functional>
#include <string>


//#include <algorithm>

namespace dae
{
    struct Event;
    class EventHandler final : public Singleton<EventHandler>
    {
    public:

        EventHandler();
        ~EventHandler() = default;
        EventHandler(const EventHandler&) = delete;
        EventHandler(EventHandler&&) = delete;
        EventHandler& operator= (const EventHandler&) = delete;
        EventHandler& operator= (const EventHandler&&) = delete;

        void AddListener(const std::string& eventName, std::function<void(const Event&)> function);
        void RemoveListener(const std::string& eventName, std::function<void(const Event&)> function);
        void Dispatch(const Event& event);

    private:
        std::map<std::string, std::vector<std::function<void(const Event&)>>> m_Listeners;
    };
}