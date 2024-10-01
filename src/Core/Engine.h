#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include <vector>
#include "GameMap.h"
#include "SDL_image.h"
#include "GameState.h"
#include "GameObject.h"
#include "ImageLayer.h"

#define SCREEN_WIDTH 992
#define MAX_SCREEN_WIDTH 1360
#define CAM_VIEW_WIDTH 3600
#define SCREEN_HEIGHT 640
#define MAX_SCREEN_HEIGHT 768
#define CAM_VIEW_HEIGHT 640

#define ROW_COUNT 20
#define COL_COUNT 100
#define TILE_SIZE 32

class Engine
{
    public:
        static Engine* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
        }

        bool Init();
        bool Clean();
        bool Quit();

        void Update();
        void Render();
        void Events();

        void ToggleWindowMaximization();
        void MinimizeWindow();

        void PopStateMenu();
        void PushState(GameState* current);
        void ChangeState(GameState* target);

        inline GameMap* GetMap(){return m_LevelMap;}
        inline bool IsRunning(){return m_IsRunning;}
        inline SDL_Window* GetMainWindow(){return m_Window;}
        inline SDL_Renderer* GetRenderer(){return m_Renderer;}

    private:
        Engine(){}
        bool m_IsRunning = false;
        bool m_IsMaximized = false;

        GameMap* m_LevelMap;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;
        std::vector<GameState*> m_States;
        std::vector<ImageLayer*> m_ParallaxBG;
        std::vector<GameObject*> m_GameObjects;
};

#endif // ENGINE_H
