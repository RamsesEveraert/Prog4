#pragma once
#include "BaseComponent.h"

#include <chrono>
#include <memory>

namespace dae
{
    class FPSComponent final : public BaseComponent
    {
    public:
        FPSComponent(const std::weak_ptr<GameObject>& gameObject);
        ~FPSComponent() = default;

        void Update() override;
        const int GetFPS() const;

    private:
        int m_Fps;
        float m_TimeRunning;
    };
}
