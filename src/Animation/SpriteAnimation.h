#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include "SDL.h"
#include <string>
#include "Animation.h"

class SpriteAnimation : public Animation
{
    public:
        SpriteAnimation(bool repeat = true);

        virtual void Update(float dt);
        void Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed);

//        int GetCurrFrame(){return m_CurrentFrame;}
//
//        int GetCurrSpriteRow(){return m_SpriteRow;}
//        int SetSpriteRow(int row){m_SpriteRow = row;}
//        void IncrSpriteRow(){m_SpriteRow++;}
//        void DecrSpriteRow(){m_SpriteRow--;}

    private:
        int m_AnimSpeed;
        int m_SpriteRow;
        int m_FrameCount;
        std::string m_TextureID;
};

#endif // SPRITEANIMATION_H
