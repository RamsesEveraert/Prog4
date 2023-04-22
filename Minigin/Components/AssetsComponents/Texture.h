#pragma once

#include "Component.h"

#include <string>
#include "glm/glm.hpp"
#include "SDL.h"

namespace dae
{
    class Texture2D;
    class Texture final : public Component
    {
    public:
        Texture();
        ~Texture() = default;

        const std::shared_ptr<Texture2D> GetTexture() const;
        void SetTextureByPath(const std::string& filename);
        void SetTexture(std::shared_ptr<Texture2D> texture);

    private:
        std::string m_TexturePath;
        std::shared_ptr<Texture2D> m_pTexture;
    };
}

