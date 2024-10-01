#ifndef GAMESTATE_H
#define GAMESTATE_H


class GameState
{
    public:
        virtual bool Init() = 0;
        virtual bool Exit() = 0;

        virtual void Render() = 0;
        virtual void Update() = 0;
};

#endif // GAMESTATE_H
