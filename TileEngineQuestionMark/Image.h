#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>


class Image
{
public:
	Image();
	~Image();

	///<summary>image_name is just the image name and extension. File path is assumed Sprites/</summary>
	SDL_Texture *Load_Texture(SDL_Renderer *render, std::string file_name, int &img_w, int &img_h);

private:
	SDL_Texture *img_t;


};

