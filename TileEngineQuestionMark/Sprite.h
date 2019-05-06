#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Sprite
{
public:
	Sprite(SDL_Renderer *render, std::string _path, int x, int y, int width, int height);
	~Sprite();
	void Update(float delta);
	void Draw(SDL_Renderer *render);
	bool Collisionslol(int x, int y);
	void Start_Frame(int begin_frame, int row);
	std::string Get_Path();
	std::string path;

	int x_pos, y_pos;
	SDL_Texture *sprite_t;
	SDL_Rect sprite_rect, pos_rect;
};