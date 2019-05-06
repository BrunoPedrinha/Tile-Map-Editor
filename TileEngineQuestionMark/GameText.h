#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class GameText
{
public:
	GameText(SDL_Renderer *rend, const char *font_name, int font_size, std::string font_text, SDL_Color text_colour, float x, float y);
	~GameText();

	void Render(SDL_Renderer *rend);

	bool Alive;

	TTF_Font *f;
	SDL_Rect pos_rect;
	SDL_Texture *text_t;

};

