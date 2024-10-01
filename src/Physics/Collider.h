#ifndef COLLIDER_H
#define COLLIDER_H

#include "SDL.h"
#include "Camera.h"
#include "CollisionHandler.h"

class Collider {
    public:
        inline SDL_Rect Get(){ return m_Box; }
        inline void SetBuffer(int x, int y, int w, int h){ m_Buffer = {x, y, w, h}; }

        void Set(int x, int y, int w, int h){
            m_Box = {
                x - m_Buffer.x,
                y - m_Buffer.y,
                w - m_Buffer.w,
                h - m_Buffer.h
            };
        }

        void DrawRect(){
            Vector2D cam = Camera::GetInstance()->GetPosition();
            SDL_Rect box = {(int)(m_Box.x - cam.X), (int)(m_Box.y - cam.Y), m_Box.w, m_Box.h};
            SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 127, 127, 127, 255); // The color of Rectangle Outline
            SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box); // To create the Rectangle Outline only
        }

    private:
        SDL_Rect m_Box;
        SDL_Rect m_Buffer;
        Collider* m_DrawRect;
};

#endif // COLLIDER_H
