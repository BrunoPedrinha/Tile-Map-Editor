#pragma once
#include <SDL.h>


class Display
{
public:
	Display();
	~Display();

	SDL_Renderer *Get_Renderer();
	SDL_Window *Get_Window();
	int Get_Window_Width() const;
	int Get_Window_Height() const;

private:
	SDL_Window *window = nullptr;
	SDL_Renderer *my_renderer = nullptr;
	void Create_Window();
	void Create_Renderer();
	const int SCREEN_W = 1920;
	const int SCREEN_H = 1080;
};

