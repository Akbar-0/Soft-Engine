#ifndef SEQANIMATION_H
#define SEQANIMATION_H

#include <map>
#include "SDL.h"
#include <vector>
#include <string>
#include "Animation.h"

struct Sequence {
    int Speed;
    int FrameCount;
    int Width, Height;
    std::vector<std::string> TextureIDs;
};

class SeqAnimation : public Animation
{
    public:
        SeqAnimation(bool repeat = true);

        virtual void Update(float dt);
        void Parse(std::string source);
        void SetCurrentSeq(std::string seqID);
        void SetRepeat(bool repeat){m_Repeat = repeat;}
        void DrawFrame(float x, float y, float xScale = 1, float yScale = 1, float scrollRatio = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        Sequence m_CurrentSeq;
        std::map<std::string, Sequence> m_SeqMap;
};

#endif // SEQANIMATION_H
