#include "TextureLoader.h"
#include "SDL_ttf.h"
#include <iostream>

int TextureLoader::height = 0;
int TextureLoader::width = 0;

SDL_Texture* TextureLoader::loadTextureFromImage(std::string path,SDL_Renderer* renderer,int flags)
{
    SDL_Texture* texture = nullptr;
    IMG_Init(flags);
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        std::cout << "Can't load image from path: " << path << "IMG_Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == NULL)
        {
            std::cout << "Cant create texture Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return texture;
}

SDL_Texture* TextureLoader::loadTextureFromText(std::string text, SDL_Color color,int size, SDL_Renderer* renderer)
{
    TTF_Font* font = TTF_OpenFont("../assets/Silkscreen/slkscr.ttf", size);
    if (font == NULL)
    {
        std::cout << "Cant load font TTF_Error: " << TTF_GetError() << std::endl;
    }
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    width = surface->w;
    height = surface->h;
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return textTexture;
}
