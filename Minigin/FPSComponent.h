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
        const int getFPS() const;

    private:
        int m_fps;
        float m_timeRunning;
    };
}
