#include "TextureLoader.h"
#include "SDL_ttf.h"

int TextureLoader::height = 0;
int TextureLoader::width = 0;

SDL_Texture* TextureLoader::loadTextureFromImage(std::string path,SDL_Renderer* renderer,int flags)
{
    SDL_Texture* newTexture = nullptr;
    IMG_Init(flags);
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

SDL_Texture* TextureLoader::loadTextureFromText(std::string text, SDL_Color color,int size, SDL_Renderer* renderer)
{
    TTF_Font* font = TTF_OpenFont("../assets/Silkscreen/slkscr.ttf", size);
    if (font == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    width = textSurface->w;
    height = textSurface->h;
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    return textTexture;
}
