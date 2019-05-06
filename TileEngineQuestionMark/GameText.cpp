#include "GameText.h"



GameText::GameText(SDL_Renderer *rend, const char *font_name, int font_size, std::string font_text, SDL_Color text_colour, float x, float y)
{

	f = TTF_OpenFont(font_name, font_size);
	if (f == NULL) std::cout << "Error f is NULL error = " << TTF_GetError() << std::endl;
	SDL_Surface *s = TTF_RenderText_Solid(f, font_text.c_str(), text_colour);
	if (s == NULL) {
		std::cout << "Error surf not working " << IMG_GetError() << std::endl;
	}

	pos_rect.x = x;
	pos_rect.y = y;
	pos_rect.w = s->w;
	pos_rect.h = s->h;

	text_t = SDL_CreateTextureFromSurface(rend, s);

	Alive = true;
}


GameText::~GameText()
{
}

void GameText::Render(SDL_Renderer *rend) {
	SDL_Rect r{ pos_rect.x, pos_rect.y, pos_rect.w, pos_rect.h };


	if (Alive) {
		SDL_RenderCopy(rend, text_t, NULL, &r);
	}
}


