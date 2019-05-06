#pragma once
#include "Tile.h"
#include "Image.h"
#include <vector>
#include <fstream>
#include <Windows.h>
#include "Camera.h"
#include <algorithm>
#include "Display.h"
const int WIDTH = 100;
const int HEIGHT = 100;
const int TOTAL_TILES = 1000;



class Editor : public Display
{
public:
	Editor();
	~Editor();

	void Load_Default_Map(SDL_Renderer *my_renderer);

	void New_Map(SDL_Renderer *my_renderer);
	void Save_Map();
	void Load_Map(SDL_Renderer *my_renderer);
	void Import_Tile(SDL_Renderer *my_renderer);

	void Set_Tile(SDL_Renderer *my_renderer, int &mouses_x, int &mouses_y);
	void Sel_Tile(SDL_Renderer *my_renderer, const int screen_height, int mouses_x, int mouses_y);

	void Zoom(float zoom_v);
	float Get_Zoom() const;

	void Update(int &mouses_x, int &mouses_y);
	void Render_Map(SDL_Renderer *my_renderer);

	void Render_HUD_Tiles(SDL_Renderer *my_renderer);

	void Set_Map_Width(int& value) { map_width = value; }
	void Set_Map_Height(int& value) { map_height = value; }

	int Get_Map_Width() const { return map_width; }
	int Get_Map_Height() const { return map_height; }
	

private:
	int map_width, map_height;
	float zoom = 1.0f;
	int total_tiles_to_draw = 2;
	int t_ref = 1;
	int tx = 0, ty = 0;
	int fx = 0, fy = 0;

	std::vector<Tile*> tile_to_select;

	//Tile *tiles[WIDTH][HEIGHT];
	std::vector<Tile*>tile_map_vector;
	Tile *seld_tile;

	//SDL_Texture *tile_texture;
	Image img_c;
	std::vector<SDL_Texture*>tile_textures;
	std::vector<SDL_Rect>texture_rect;

	char file_name[MAX_PATH];
	OPENFILENAME open_file_name;
	Camera *c;

};

