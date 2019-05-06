#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>



class Tile
{
public:

	
	
	


	Tile(int x, int y, int w, int h, int t_ref);

	~Tile();
	bool Collision_Check(SDL_Rect &A, SDL_Rect &B);
	void Render(SDL_Renderer *rend, SDL_Rect camera, float zoom);

	void Draw(SDL_Renderer *rend);
	void Update(SDL_Rect cam);

	std::string Get_File_Path();
	///<summary>Returns if the tile is alive or not.</summary>
	bool Alive();

	///<summary>Set src rect img dimensions - imported img dimensions</summary>
	void Set_Tile_Img_Dimensions(int img_w, int img_h);

	///<summary>Set the tile texture so we can draw the tile. NULL until you initialize with this</summary>
	void Set_Tile_Texture(SDL_Texture *_tile_t);

	///<summary>Return tile id</summary>
	int Get_Tile_Ref() const;

	///<summary>Return tile rect</summary>
	SDL_Rect Get_Tile_Rect() const;


private:
	std::string file_path_name;
	SDL_Texture *tile_t;
	SDL_Rect tile_rect, tile_pos;
	int texture_w, texture_h, tile_ref;
	bool alive;
};

