#pragma once
#include "RenderComponent.h"
#include "Texture.h"

namespace dae
{
    class Texture;
    class TextureRenderer : public RenderComponent
    {
    public:
        TextureRenderer();
        virtual ~TextureRenderer() = default;

        virtual void Render() override;

    private:
        void CheckTexture();

        Texture* m_pTexture;
    };
}
