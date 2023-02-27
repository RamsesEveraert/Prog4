#pragma once

#include "BaseComponent.h"

namespace dae
{

    //TODO: later

    class PhysicsComponent final : public BaseComponent
    {
    public:
        PhysicsComponent(const std::weak_ptr<GameObject>& gameObject);
        ~PhysicsComponent() = default;

        //TODO: functions

    private:

    };
}


