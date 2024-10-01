#include "ImageLayer.h"
#include "TextureManager.h"

ImageLayer::ImageLayer(std::string m_TextureID, int x, int y, float scrollRatio, float scaleX, float scaleY, float angle, SDL_RendererFlip flip)
{
    this->m_TextureID = m_TextureID;
    m_Flip = flip;
    m_OffsetX = x;
    m_OffsetY = y;
    m_Angle = angle;
    m_Repeated = true;
    m_ScaleX = scaleX;
    m_ScaleY = scaleY;
    QueryImage(m_TextureID);
    m_ScrollRatio = scrollRatio;
}

void ImageLayer::Render()
{
    TextureManager::GetInstance()->Draw(m_TextureID, m_OffsetX, m_OffsetY, m_ImgWidth, m_ImgHeight, m_ScrollRatio, m_ScaleX, m_ScaleY, 180 - m_Angle, m_Flip);
}

void ImageLayer::Update()
{
    //
}

void ImageLayer::QueryImage(std::string textureID)
{
    SDL_Texture* texture = TextureManager::GetInstance()->GetTexture(m_TextureID);
    SDL_QueryTexture(texture, nullptr, nullptr, &m_ImgWidth, &m_ImgHeight);
}
