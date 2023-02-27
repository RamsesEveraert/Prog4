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
        int m_frames;
        int m_fps;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    };
}
