#include "Sprite.h"



Sprite::Sprite(SDL_Renderer *render, std::string _path, int x, int y, int width, int height)
{
	path = _path;
	SDL_Surface *surf = IMG_Load(path.c_str());
	if (surf == NULL) {
		std::cout << "Error surf not working " << IMG_GetError() << std::endl;
	}
	else {
		sprite_t = SDL_CreateTextureFromSurface(render, surf);
		if (sprite_t == NULL) std::cout << "Error img" << std::endl;
	}
	SDL_FreeSurface(surf);

	SDL_QueryTexture(sprite_t, NULL, NULL, &sprite_rect.w, &sprite_rect.h);

	pos_rect.x = x;
	pos_rect.y = y;
	pos_rect.w = width;
	pos_rect.h = height;
}


Sprite::~Sprite()
{
}

void Sprite::Update(float delta) {

}

void Sprite::Draw(SDL_Renderer *render) {
	SDL_RenderCopy(render, sprite_t, &sprite_rect, &pos_rect);
}

bool Sprite::Collisionslol(int x, int y) {

	SDL_GetMouseState(&x, &y);

	if ((x > pos_rect.x) && (x < pos_rect.x + pos_rect.w) && (y > pos_rect.y) && (y < pos_rect.y + pos_rect.h)) {
		return true;
	}

	return false;
}

std::string Sprite::Get_Path() {
	return path;
}
