#include "Camera.h"
Camera* Camera::instance = NULL;

Camera::Camera() {
	cam_dimensions.x = -480;
	cam_dimensions.y = 0;
	cam_dimensions.w = 1920;
	cam_dimensions.h = 1080;

}

Camera::~Camera() {
	instance = NULL;
}

Camera* Camera::Get_Instance() {
	if (instance == NULL)
		instance = new Camera();
	return instance;
}

SDL_Rect Camera::Get_Cam_Rect() {
	return cam_dimensions;
}

void Camera::Move_Cam_X(int value) {
	cam_dimensions.x += value;
}

void Camera::Move_Cam_Y(int value) {
	cam_dimensions.y += value;
}

void Camera::Update(SDL_Rect player_rect, SDL_Rect ai_rect, const int map_width, const int map_height, const int screen_width, const int screen_height) {

	
}
