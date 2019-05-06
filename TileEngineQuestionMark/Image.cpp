#include "Image.h"



Image::Image()
{
}


Image::~Image()
{
}

SDL_Texture* Image::Load_Texture(SDL_Renderer *render, std::string file_name, int &img_w, int &img_h) {
	//std::string path = "Sprites/" + file_name;

	SDL_Surface *surf = IMG_Load(file_name.c_str());
	if (surf == NULL) {
		std::cout << "Error surf not working " << IMG_GetError() << std::endl;
	}
	else {
		img_t = SDL_CreateTextureFromSurface(render, surf);
		if (img_t == NULL) std::cout << "Error img" << IMG_GetError() << std::endl;
	}
	SDL_FreeSurface(surf);

	SDL_QueryTexture(img_t, NULL, NULL, &img_w, &img_h);

	return img_t;
}
