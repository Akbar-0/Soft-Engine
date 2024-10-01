#include "Menu.h"

#include "Play.h"
#include "Input.h"
#include "Engine.h"

Menu::Menu()
{
    //ctor
}
bool Menu::Init()
{
    m_Context = Engine::GetInstance()->GetRenderer();
    std::cout << "Menu Initialized!" << std::endl;
    return true;
}

void Menu::Render()
{
    SDL_SetRenderDrawColor(m_Context, 50, 50, 100, 255);
    SDL_RenderClear(m_Context);

    SDL_RenderPresent(m_Context);
}

void Menu::Update()
{

}

bool Menu::Exit()
{
    std::cout << "Menu Exited!" << std::endl;
    return true;
}

void Menu::StartGame()
{
    std::cout << "Game Started!" << std::endl;
}

void Menu::Settings()
{
    std::cout << "Settings Opened!" << std::endl;
}

void Menu::Editor()
{
    std::cout << "Editor Opened!" << std::endl;
}

void Menu::Quit()
{
    std::cout << "Game Exited!" << std::endl;
}
