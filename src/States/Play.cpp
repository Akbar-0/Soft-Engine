#include "Play.h"

//Play* Play::s_Instance = nullptr;

Play::Play()
{
    //ctor
}

bool Play::Init()
{
    m_EditMode = false;
    m_Context = Engine::GetInstance()->GetRenderer();

    TextureManager::GetInstance()->ParseTextures("assets/textures.tml");
    m_LevelMap = MapParser::GetInstance()->Load("assets/maps/map.tmx");
    TileLayer* collisionLayer = (TileLayer*)m_LevelMap->GetMapLayers().front();
    collisionTilemap = collisionLayer->GetTilemap();

    int tileSize = TILE_SIZE;
    int screenWidth = COL_COUNT * TILE_SIZE;
    int screenHeight = ROW_COUNT * TILE_SIZE;

    Warrior* player = new Warrior(new Properties("player_idle", 0, 299, 128, 128));
    Camera::GetInstance()->SetTarget(player->GetOrigin());
    m_GameObjects.push_back(player);

    std::cout << "Play Initialized!" <<std::endl;
    return true;
}

void Play::Render()
{
    Events();
    SDL_SetRenderDrawColor(m_Context, 50, 50, 100, 255);
    SDL_RenderClear(m_Context);

    m_LevelMap->Render();

    if(m_EditMode){
        std::cout << "EditMode Activated" << std::endl;
        // Code to Display Menu
    }

    for(auto gameObj : m_GameObjects)
        gameObj->Draw();

    SDL_Rect camera = Camera::GetInstance()->GetViewBox();

    SDL_RenderCopy(m_Context, nullptr, &camera, nullptr);
    SDL_RenderPresent(m_Context);
}

void Play::Update()
{
    Events();

    if(!m_EditMode){
        float dt = Timer::GetInstance()->GetDeltaTime();

//        for(auto gameObj : m_GameObjects)
//            gameObj->Update(dt);

        Camera::GetInstance()->Update(dt);
        m_LevelMap->Update();
    }
}

void Play::Events()
{
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){
        if(m_EditMode){
            m_EditMode = false;
        }else{
            m_EditMode = true;
        }
    }

    SDL_Delay(100);
}

bool Play::Exit()
{
    delete m_LevelMap;

    for(auto gameObj : m_GameObjects)
        delete gameObj;

//    delete s_Instance;
//    s_Instance = nullptr;
    m_GameObjects.clear();
    TextureManager::GetInstance()->Clean();
    std::cout << "Play Exited" << std::endl;

    return true;
}

void Play::OpenMenu()
{
    Engine::GetInstance()->ChangeState(new Menu());///////////////////////////////////////////////////
}

void Play::PauseGame()
{

}
