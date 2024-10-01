#ifndef PLAY_H
#define PLAY_H

#include "Menu.h"
#include "Input.h"
#include "Enemy.h"
#include "Timer.h"
#include "Engine.h"
#include "Camera.h"
#include <iostream>
#include "GameMap.h"
#include "Warrior.h"
#include "GameState.h"
#include "MapParser.h"
#include "TileLayer.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "TextureManager.h"
#include "CollisionHandler.h"

class Play : public GameState
{
    public:
        Play();
        void Events();

        virtual bool Init();
        virtual bool Exit();
        virtual void Render();
        virtual void Update();

        //inline GameMap* GetMap(){return m_LevelMap;}
//        static Play* GetInstance(){return s_Instance = (s_Instance != nullptr) ? s_Instance : new Play();}

    private:
        static void OpenMenu();
        static void PauseGame();

    private:
        bool m_EditMode;
//        static Play* s_Instance;/////////////////////////////////////////////////
        GameMap* m_LevelMap;
        SDL_Renderer* m_Context;
        TileMap collisionTilemap;
        std::vector<GameObject*> m_GameObjects;
};

#endif // PLAY_H
