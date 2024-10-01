#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include "SDL.h"
#include <string>
#include "tinyxml.h"

using TextureMap = std::map<std::string, SDL_Texture*>;
class TextureManager
{
    public:
        static TextureManager* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();
        }

        bool Load(std::string id, std::string filename);
        bool ParseTextures(std::string source);
        void Drop(std::string id);
        void Clean();

        void Draw(std::string id, int x, int y, int width, int height, float scrollRatio = 0, float xScale = 1, float yScale = 1, float angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE); // For Single Frames e.g., BackGround
        void DrawTile(std::string tilesetID, int tileSize, float x, float y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE); // For Drawing Map
        void DrawFrame(std::string id, float x, float y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE); // For multiple frame Animations e.g., Player, Enemy, etc.

        TextureMap GetTextureMap(){return m_TextureMap;}
        SDL_Texture* GetTexture(std::string id){return m_TextureMap[id];}

    private:
        TextureManager(){}
        TextureMap m_TextureMap;
        static TextureManager* s_Instance;
};

#endif // TEXTUREMANAGER_H
