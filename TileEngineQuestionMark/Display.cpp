#include "Display.h"



Display::Display(){
	SDL_Init(SDL_INIT_VIDEO);
	Create_Window();
	Create_Renderer();
}

Display::~Display()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(my_renderer);
}

SDL_Renderer *Display::Get_Renderer() {
	return my_renderer;
}

SDL_Window *Display::Get_Window() {
	return window;
}

int Display::Get_Window_Height() const {
	return SCREEN_H;
}


int Display::Get_Window_Width() const {
	return SCREEN_W;
}

void Display::Create_Window() {
	window = SDL_CreateWindow(
		"Tile Editor",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_W, SCREEN_H,
		SDL_WINDOW_MAXIMIZED);
}

void Display::Create_Renderer() {
	my_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}