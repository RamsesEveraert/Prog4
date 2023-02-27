#pragma once

#include "BaseComponent.h"

namespace dae
{

    //TODO: later

    class InputComponent final : public BaseComponent
    {
    public:
        InputComponent(const std::weak_ptr<GameObject>& gameObject);
        ~InputComponent() = default;

        //TODO: functions

    private:

    };
}


