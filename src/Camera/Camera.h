#ifndef CAMERA_H
#define CAMERA_H

#include "SDL.h"
#include "Point.h"
#include "Engine.h"
#include "Vector2D.h"

class Camera
{
    public:
        void Update(float dt);
        void SetMaxDisplay(){screenHeight = /*MAX_*/SCREEN_HEIGHT; screenWidth = MAX_SCREEN_WIDTH;}
        void RestoreDisplay(){screenHeight = SCREEN_HEIGHT; screenWidth = SCREEN_WIDTH;}

        inline int GetSceneHeight(){return screenWidth;}
        inline int GetSceneWidth(){return screenWidth;}

        inline SDL_Rect GetViewBox() {return m_ViewBox;}
        inline Vector2D GetPosition() {return m_Position;}

        inline void SetTarget(Point* target) {m_Target = target;}
        inline void SetSceneLimit(int w, int h){screenWidth = w; screenHeight = h;}

        inline void MoveX(float x){m_Position.X = x;}
        inline void MoveY(float y){m_Position.Y = y;}

        inline static Camera* GetInstance() {return s_Instance = (s_Instance != nullptr)? s_Instance : new Camera();}

    private:
        Camera(){
            m_ViewBox = {0, 0, /*screenWidth*/SCREEN_WIDTH, /*screenHeight*/SCREEN_HEIGHT};
        }

        Point* m_Target;
        Vector2D m_Position;
        int screenWidth = SCREEN_WIDTH;
        int screenHeight = SCREEN_HEIGHT;

        SDL_Rect m_ViewBox;
        static Camera* s_Instance;
};

#endif // CAMERA_H
