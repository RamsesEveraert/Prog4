#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <string>
#include <any>

namespace dae
{
    struct Event
    {
        std::string name;
        std::vector<std::any> data; // https://devblogs.microsoft.com/cppblog/stdany-how-when-and-why/
        bool operator==(const Event& other)
        {
            return name == other.name;
        }
    };

}
