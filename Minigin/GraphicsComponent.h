#pragma once

#include "BaseComponent.h"

namespace dae
{

    //TODO: later

    class GraphicsComponent final : public BaseComponent
    {
    public:
        GraphicsComponent(const std::weak_ptr<GameObject>& gameObject);
        ~GraphicsComponent() = default;

        //TODO: functions

    private:
     
    };
}
