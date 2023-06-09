#pragma once
#include "RenderComponent.h"
#include "Sprite.h"

namespace dae
{
    class Sprite;
    class SpriteRenderer : public RenderComponent
    {
    public:
        SpriteRenderer();
        virtual ~SpriteRenderer() = default;

        virtual void Render() override;

    private:
        bool HasSprite();


        Sprite* m_pSprite;
    };
}