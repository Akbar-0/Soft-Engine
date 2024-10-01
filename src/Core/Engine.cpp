#include "Engine.h"

#include "Play.h"
#include "Input.h"
#include "Timer.h"
#include "Enemy.h"
#include "Camera.h"
#include "Warrior.h"
#include "MapParser.h"
#include "GameState.h"
#include "ObjectFactory.h"
#include "TextureManager.h"

Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO)!= 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)!= 0){
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("SoftEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if(m_Window == nullptr){
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr){
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

//    GameState* play = new Play();////////////////////////////
//    m_States.push_back(play);////////////////////////////////

    MapParser::GetInstance()->Load("assets/maps/map.tmx");
//    if(!MapParser::GetInstance()->Load("assets/maps/map.tmx")){
//        std::cerr << "\n|=|=|=|=|=|--Failed to Load Map--|=|=|=|=|=|\n" << std::endl;
//    }

    /// Load the Level Map
    m_LevelMap = MapParser::GetInstance()->GetMap("level1");

    /// Parse All Textures (Characters, Backgrounds, etc.)
    TextureManager::GetInstance()->ParseTextures("assets/textures.tml");
    //TextureManager::GetInstance()->Load("player_idle", "assets/Idle.png");

    m_ParallaxBG.push_back(new ImageLayer("parallax_2", 0, -150, 0.5, 1, 1, 0, SDL_FLIP_NONE));

    /// Create Game Characters
    Properties* props = new Properties("player_idle", 0, 299, 128, 128);

    GameObject* player = ObjectFactory::GetInstance()->CreateObject("PLAYER", props);
    //Warrior* player = new Warrior(new Properties("player_idle", 0, 299, 128, 128));
    Enemy* test = new Enemy(new Properties("manW", 700, 200, 46, 70));
    m_GameObjects.push_back(player);
    m_GameObjects.push_back(test);

//    for(unsigned int i = 0; i != m_States.size(); i++)///////////////////////////
//        m_States[i]->Init();/////////////////////////////////////////////////////

    Camera::GetInstance()->SetTarget(player->GetOrigin());
    return m_IsRunning = true;
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 50, 50, 100, 255);
    SDL_RenderClear(m_Renderer);

    //TextureManager::GetInstance()->Draw("bg", 0, 0, 1920, 640, 0.5, 1, 1, SDL_FLIP_NONE);

    /// Render Background Layers
    for(unsigned int i = 0; i != m_ParallaxBG.size(); i++)
        m_ParallaxBG[i]->Render();

    m_LevelMap->Render();

//    for(unsigned int i = 0; i != m_States.size(); i++)////////////////////////////
//        m_States[i]->Render();////////////////////////////////////////////////////

    /// Render Game Characters
    for(unsigned int i = 0; i != m_GameObjects.size(); i++)
        m_GameObjects[i]->Draw();

    SDL_RenderPresent(m_Renderer);
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();

//    for(unsigned int i = 0; i != m_States.size(); i++)//////////////////////////////
//        m_States[i]->Update();//////////////////////////////////////////////////////

    /// Update Game Characters
    for(unsigned int i = 0; i != m_GameObjects.size(); i++)
        m_GameObjects[i]->Update(dt);

    /// Update Background Layers
//    for(unsigned int i = 0; i != m_ParallaxBG.size(); i++)
//        m_ParallaxBG[i]->Update();

    Camera::GetInstance()->Update(dt);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

void Engine::ToggleWindowMaximization()
{
    if (m_Window) {
        if (m_IsMaximized) {
            SDL_RestoreWindow(m_Window);
            Camera::GetInstance()->RestoreDisplay();
        } else {
            SDL_MaximizeWindow(m_Window);
            Camera::GetInstance()->SetMaxDisplay();
        }
        m_IsMaximized = !m_IsMaximized;
    }
}

void Engine::MinimizeWindow()
{
    if (m_Window) {
        SDL_MinimizeWindow(m_Window);
    }
}

bool Engine::Clean()
{
//    for(unsigned int i = 0; i != m_States.size(); i++)///////////////////////////
//        m_States[i]->Exit();/////////////////////////////////////////////////////

    for(unsigned int i = 0; i != m_GameObjects.size(); i++)
        m_GameObjects[i]->Clean();

    TextureManager::GetInstance()->Clean();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();

    return true;
}

bool Engine::Quit()
{
    m_IsRunning = false;

    return true;
}

void Engine::PopStateMenu()
{
    std::cerr << "Menu Popped" << std::endl;
}

void Engine::PushState(GameState* current)
{
    m_States.push_back(current);
    std::cerr << "State Pushed" << std::endl;
}

void Engine::ChangeState(GameState* target)
{
    m_States.push_back(target);
    std::cerr << "State Changed" << std::endl;
}
