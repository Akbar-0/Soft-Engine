#ifndef IMAGELAYER_H
#define IMAGELAYER_H

#include "SDL.h"
#include <string>
#include "Layer.h"
#include <iostream>
#include "SDL_image.h"

class ImageLayer : public Layer
{
    public:
        ImageLayer(std::string m_TextureID, int x, int y, float scrollRatio = 1.0f, float scaleX = 1.0f, float scaleY = 1.0f, float angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetScrollRatio(float scrollRatio){m_ScrollRatio = scrollRatio;}
        void SetOffset(int x, int y){m_OffsetX = x; m_OffsetY = y;}
        void SetRepeated(bool repeated){m_Repeated = repeated;}
        void QueryImage(std::string textureID);

        virtual void Render();
        virtual void Update();

    protected:

    private:
        bool m_Repeated;
        float m_ScrollRatio;
        std::string m_TextureID;
        float m_ScaleX, m_ScaleY, m_Angle;
        int m_OffsetX, m_OffsetY;
        int m_ImgWidth, m_ImgHeight;
        SDL_RendererFlip m_Flip;

};

#endif // IMAGELAYER_H
