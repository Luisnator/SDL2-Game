#pragma once
#include "Gameobject.h"
#include <string>
#include "TextureLoader.h"
class TextRender :
    public Gameobject
{
public:
    TextRender(SDL_Rect position,std::string text, int size, SDL_Color c, Game* instance);
    ~TextRender();

    SDL_Texture* tex;

    void update(int delta);
    void render();

    std::string text = "";
    int font_size;
    SDL_Color c = { 0,0,0 };
    int height = 0;
    int width = 0;
    bool change = false;

    void setColor(SDL_Color c);
    void setSize(int size);
    void setPosition(SDL_Rect position);
    void setText(std::string text);
};

