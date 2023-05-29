#pragma once

#include "Component.h"


#include "SDL.h"
#include "glm/glm.hpp"

namespace dae
{
    class Texture2D;
    class Sprite final : public Component
    {
    public:
        Sprite(const std::string& spritePath, const SDL_Rect& spriteSrc, float scale = 1);
        virtual ~Sprite() = default;

        virtual void Update() override {};
        virtual void Render()  override {};

        void SetPosition(const glm::vec2& position);
        const glm::vec2& GetPosition() const;

        void SetSize(int width, int height);
        glm::vec2 GetSize() const;

        void SetColor(const SDL_Color& color);
        const SDL_Color& GetColor() const;

        void SetAlpha(Uint8 alpha);
        Uint8 GetAlpha() const;

        void SetFlip(const SDL_RendererFlip& flip);
        const SDL_RendererFlip& GetFlip() const;

        void SetRotation(float angle);
        float GetRotation() const;

        void SetSpriteSrc(const SDL_Rect& spriteSrc);
        const SDL_Rect& GetSpriteSrc() const;

        void SetScale(const glm::vec2& scale);
        const glm::vec2& GetScale() const;

        void SetTexture(const std::string& path);
        const std::shared_ptr<dae::Texture2D> GetTexture() const;

    private:
        std::shared_ptr<Texture2D> m_pTexture;
        SDL_Rect m_SrcRect;
        glm::vec2 m_Position;
        glm::vec2 m_Size;
        SDL_Color m_Color;
        Uint8 m_Alpha;
        SDL_RendererFlip m_Flip;
        float m_Angle;
        glm::vec2 m_Scale;
    };

}






