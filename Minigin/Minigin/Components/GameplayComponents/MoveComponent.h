#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace dae
{
    class GameObject;
    class MovementComponent final : public BaseComponent
    {
    public:

        MovementComponent() = default;
        void Move(const glm::vec2& direction);
        void SetSpeed(float speed);
        const float GetSpeed() const;
        

    private:
        float m_Speed;
    };

}