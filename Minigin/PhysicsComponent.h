#pragma once

#include "BaseComponent.h"

namespace dae
{

    //TODO: later

    class PhysicsComponent final : public BaseComponent
    {
    public:
        PhysicsComponent(std::weak_ptr<GameObject> pOwner, const std::string& identifier = "");
        ~PhysicsComponent() = default;

        //TODO: functions

    private:

    };
}


