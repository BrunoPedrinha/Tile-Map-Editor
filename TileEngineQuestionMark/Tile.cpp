#include "Tile.h"



Tile::Tile(int x, int y, int w, int h, int t_ref)
{
	

	tile_pos.x = x;
	tile_pos.y = y;
	tile_pos.w = w;
	tile_pos.h = h;

	alive = true;

	tile_ref = t_ref;


}


Tile::~Tile()
{
	SDL_DestroyTexture(tile_t);
}

void Tile::Set_Tile_Img_Dimensions(int img_w, int img_h) {
	tile_rect.w = img_w;
	tile_rect.h = img_h;
}

void Tile::Set_Tile_Texture(SDL_Texture *_tile_t) {
	tile_t = _tile_t;
}

int Tile::Get_Tile_Ref() const {
	return tile_ref;
}


SDL_Rect Tile::Get_Tile_Rect() const {
	return tile_pos;
}
void Tile::Update(SDL_Rect cam) {
	if (tile_pos.x + tile_pos.w < cam.x || tile_pos.x > cam.x + cam.w
		|| tile_pos.y + tile_pos.h < cam.y || tile_pos.y > cam.y + cam.h)
		alive = false;

	else alive = true;
}

std::string Tile::Get_File_Path() {
	return file_path_name;
}

void Tile::Render(SDL_Renderer *rend, SDL_Rect camera, float zoom) {
	if (alive) {
		SDL_Rect f = { (tile_pos.x*zoom) - camera.x, (tile_pos.y*zoom) - camera.y, tile_pos.w*zoom, tile_pos.h*zoom };

		SDL_RenderCopy(rend, tile_t, NULL, &f);
	}
	
}
void Tile::Draw(SDL_Renderer *rend) {
	SDL_RenderCopy(rend, tile_t, &tile_rect, &tile_pos);
}


