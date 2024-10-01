#include "SeqAnimation.h"

#include <iostream>
#include "tinyxml.h"
#include "TextureManager.h"

SeqAnimation::SeqAnimation(bool repeat):Animation(repeat){}

void SeqAnimation::Update(float dt)
{
    if(m_Repeat || !m_IsEnded){
        m_IsEnded = false;
        m_CurrentFrame = (SDL_GetTicks()/m_CurrentSeq.Speed) % m_CurrentSeq.FrameCount;
    }

    if(!m_Repeat && m_CurrentFrame == (m_CurrentSeq.FrameCount-1)){
        m_IsEnded = true;
        m_CurrentFrame = (m_CurrentSeq.FrameCount - 1);
    }
}

void SeqAnimation::Parse(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cerr << "Failed to load animation file: " << source << std::endl;
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e= root->FirstChildElement(); e != nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("sequence")){
                Sequence seq;
                std::string seqID = e->Attribute("id");
                e->Attribute("frameCount", &seq.FrameCount);
                e->Attribute("speed", &seq.Speed);
                e->Attribute("width", &seq.Width);
                e->Attribute("height", &seq.Height);

                for(TiXmlElement* frame= e->FirstChildElement(); frame != nullptr; frame=frame->NextSiblingElement()){
                    seq.TextureIDs.push_back(frame->Attribute("textureID"));
                }

                m_SeqMap[seqID] = seq;
        }
    }
}

void SeqAnimation::SetCurrentSeq(std::string seqID)
{
    if(m_SeqMap.count(seqID) > 0){
        m_CurrentSeq = m_SeqMap[seqID];
    }
    else{
        std::cout << "The given Animation Sequence is not matching: " << seqID << std::endl;
    }
}

void SeqAnimation::DrawFrame(float x, float y, float xScale, float yScale, float scrollRatio, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->Draw(m_CurrentSeq.TextureIDs[m_CurrentFrame], x, y, m_CurrentSeq.Width, m_CurrentSeq.Height, scrollRatio, xScale, yScale, flip);
}
