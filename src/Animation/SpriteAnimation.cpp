#include "SpriteAnimation.h"

#include "TextureManager.h"

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat){}

void SpriteAnimation::Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale, float yScale, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_CurrentFrame, flip);
}

void SpriteAnimation::Update(float dt)
{
    m_CurrentFrame = (SDL_GetTicks()/m_AnimSpeed) % m_FrameCount;
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed)
{
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_AnimSpeed = animSpeed;
    m_FrameCount = frameCount;
}

