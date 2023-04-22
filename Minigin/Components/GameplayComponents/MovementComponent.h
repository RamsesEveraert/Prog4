#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
    class GameObject;
    class MovementComponent final : public Component
    {
    public:

        MovementComponent();
        void Move(const glm::vec2& direction);
        void SetSpeed(float speed);
        const float GetSpeed() const;
        

    private:
        float m_Speed;
    };

}