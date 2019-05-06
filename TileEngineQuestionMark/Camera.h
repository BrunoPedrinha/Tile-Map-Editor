#pragma once
#include <SDL.h>
#include <cstddef>
#include <iostream>

class Camera {

private:
	static Camera* instance;
	Camera();
	SDL_Rect cam_dimensions;
	float time_passed;

public:
	static Camera* Get_Instance();
	~Camera();
	SDL_Rect Get_Cam_Rect();
	void Move_Cam_X(int value);
	void Move_Cam_Y(int value);
	void Update(SDL_Rect player_rect, SDL_Rect ai_rect, const int map_width, const int map_height, const int screen_width, const int screen_height);
};

