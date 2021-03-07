#include "TextRender.h"

TextRender::TextRender(SDL_Rect position,std::string text,int size ,SDL_Color c,Game* instance):Gameobject(instance)
{
	this->c = c;
	this->font_size = size;
	this->text = text;
	this->position = position;
}

TextRender::~TextRender()
{
	SDL_DestroyTexture(tex);
}

void TextRender::update(int delta)
{
	if (change)
	{
		SDL_DestroyTexture(tex);
		tex = TextureLoader::loadTextureFromText(text, c, font_size, instance->renderer);
		position.h = TextureLoader::height;
		position.w = TextureLoader::width;
		change = false;
	}
}

void TextRender::render()
{
	SDL_RenderCopy(instance->renderer, tex, NULL, &position);
}

void TextRender::setColor(SDL_Color c)
{
	if ((c.r != this->c.r) or (c.g != this->c.g) or (c.b != this->c.b))
	{
		this->c = c;
		change = true;
	}
}

void TextRender::setSize(int size)
{
	this->font_size = size;
	change = true;
}

void TextRender::setPosition(SDL_Rect position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	change = true;
}

void TextRender::setText(std::string text)
{
	if (text != this->text)
	{
		this->text = text;
		change = true;
	}
}
