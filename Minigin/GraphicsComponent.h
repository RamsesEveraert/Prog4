#pragma once

#include "BaseComponent.h"

namespace dae
{

    //TODO: later

    class GraphicsComponent final : public BaseComponent
    {
    public:
        GraphicsComponent(std::weak_ptr<GameObject> owner, const std::string& identifier = "");
        ~GraphicsComponent() = default;

        //TODO: functions

    private:
     
    };
}
