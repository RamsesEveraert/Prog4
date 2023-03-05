#pragma once

#include "BaseComponent.h"

namespace dae
{

    //TODO: later

    class InputComponent final : public BaseComponent
    {
    public:
        InputComponent(std::weak_ptr<GameObject> owner, const std::string& identifier = "");
        ~InputComponent() = default;

        //TODO: functions

    private:

    };
}


