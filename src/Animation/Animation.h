#ifndef ANIMATION_H
#define ANIMATION_H

//#include "SDL.h"
//#include <string>

class Animation
{
    public:
        Animation(bool repeat = true) : m_Repeat(repeat){ m_IsEnded = false; }

        virtual void Update(float dt) = 0;
        inline bool IsEnded(){return m_IsEnded;}
//        void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
//        void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed/*, SDL_RendererFlip flip = SDL_FLIP_NONE*/);

    protected:
        bool m_Repeat;
        bool m_IsEnded;
        int m_CurrentFrame;

//        int m_SpriteRow;
//        int m_SpriteFrame;
//        int m_AnimSpeed;
//        int m_FrameCount;
//        std::string m_TextureID;
        //SDL_RendererFlip m_Flip;
};

#endif // ANIMATION_H
