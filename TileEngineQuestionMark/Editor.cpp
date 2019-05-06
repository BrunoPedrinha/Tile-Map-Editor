#include "Editor.h"



Editor::Editor()
{
	c = Camera::Get_Instance();
	int def_width = 10;
	int def_height = 10;

	Set_Map_Width(def_width);
	Set_Map_Height(def_height);

	for (int i = 0; i < total_tiles_to_draw; i++) {
		std::string file_path = "Sprites/Tiles/tile" + std::to_string(i) + ".png";
		SDL_Rect temp_rect;
		SDL_Texture *t_tile_texture = img_c.Load_Texture(Get_Renderer(), file_path, temp_rect.w, temp_rect.h);
		tile_textures.push_back(t_tile_texture);
		texture_rect.push_back(temp_rect);
	}
	
	Load_Default_Map(Get_Renderer());
	
	///load the tiles you can select to place.
	for (int i = 0; i < tile_textures.size(); i++) {
		Tile *tees = new Tile(tx, ty, 48, 48, i);
		tees->Set_Tile_Texture(tile_textures[i]);
		tees->Set_Tile_Img_Dimensions(texture_rect[i].w, texture_rect[i].h);
		tile_to_select.push_back(tees);
		tx += 54;
	}

	///the tile selected
	seld_tile = new Tile(432 / 2 - 20, Get_Window_Height() - 100, 48, 48, 0);
	seld_tile->Set_Tile_Texture(tile_textures[0]);
	seld_tile->Set_Tile_Img_Dimensions(texture_rect[0].w, texture_rect[0].h);

}


Editor::~Editor(){
	delete seld_tile;
	for (int i = 0; i < tile_to_select.size(); i++)
		delete tile_to_select[i];
	tile_to_select.clear();
	for (int i = 0; i < tile_map_vector.size(); i++)
		delete tile_map_vector[i];
	tile_map_vector.clear();

	for (int i = 0; i < tile_textures.size(); i++) {
		SDL_DestroyTexture(tile_textures[i]);
	}
	tile_textures.clear();

	c->~Camera();
	Display::~Display();
}

void Editor::Update(int &mouses_x, int &mouses_y) {

	if (mouses_x < 32)
		c->Move_Cam_X(-1);
	if (mouses_x > 1920 - 32)
		c->Move_Cam_X(1);
	if (mouses_y < 32)
		c->Move_Cam_Y(-1);
	if (mouses_y > 1080 - 32)
		c->Move_Cam_Y(1);

	mouses_x += c->Get_Cam_Rect().x;
	mouses_y += c->Get_Cam_Rect().y;

}

void Editor::Load_Default_Map(SDL_Renderer *my_renderer) {
	///load all black tiles.

	

	for (int x = 0; x < Get_Map_Width(); x++) {
		for (int y = 0; y < Get_Map_Height(); y++) {
			Tile *test_tiler = new Tile(x * 48, y * 48, 48, 48, 1);
			test_tiler->Set_Tile_Texture(tile_textures[1]);
			test_tiler->Set_Tile_Img_Dimensions(texture_rect[1].w, texture_rect[1].h);
			tile_map_vector.push_back(test_tiler);
		}
	}
}

void Editor::Save_Map() {
	std::ofstream new_map("level.level");

	if (new_map.is_open()) {
		new_map << Get_Map_Width();
		new_map << "\n";
		new_map << Get_Map_Height();
		new_map << "\n";
		for (int i = 0; i < tile_map_vector.size(); i++) {
				new_map << tile_map_vector[i]->Get_Tile_Ref() << " ";
		}
		
	}
	new_map.close();
	///system("attrib +r New_LevelLULtest.txt"); this makes it read only
}

void Editor::New_Map(SDL_Renderer *my_renderer) {
	for (int i = 0; i < tile_map_vector.size(); i++) {
			delete tile_map_vector[i];
		
	}
	tile_map_vector.clear();

	Load_Default_Map(my_renderer);

}

void Editor::Load_Map(SDL_Renderer *my_renderer) {

	ZeroMemory(&file_name, sizeof(file_name));
	ZeroMemory(&open_file_name, sizeof(open_file_name));
	open_file_name.lStructSize = sizeof(open_file_name);
	open_file_name.hwndOwner = NULL;
	open_file_name.lpstrFilter = "Level Files\0*.level\0";
	open_file_name.lpstrFile = file_name;
	open_file_name.nMaxFile = MAX_PATH;
	open_file_name.lpstrTitle = "Select a map";
	open_file_name.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&open_file_name)) {
		std::ifstream open_map(file_name);


		int x = 0, y = 0, test = 0;
		bool loading_tiles = true;
		for (int i = 0; i < tile_map_vector.size(); i++) {
				delete tile_map_vector[i];
			
		}
		tile_map_vector.clear();

		if (open_map.is_open()) {
			int temp_width, temp_height;
			open_map >> temp_width;
			open_map >> temp_height;
			Set_Map_Width(temp_width);
			Set_Map_Height(temp_height);

			for (int x = 0; x < Get_Map_Width(); x++) {
				for (int y = 0; y < Get_Map_Height(); y++) {

					int tile_type = -1;
					open_map >> tile_type;
					if (open_map.fail()) {
						loading_tiles = false;
						break;
					}

					Tile *test_tiler = new Tile(x * 48, y * 48, 48, 48, tile_type);
					test_tiler->Set_Tile_Texture(tile_textures[tile_type]);
					test_tiler->Set_Tile_Img_Dimensions(texture_rect[tile_type].w, texture_rect[tile_type].h);
					tile_map_vector.push_back(test_tiler);
				}
			}
		}
		open_map.close();
	}
		
}

void Editor::Import_Tile(SDL_Renderer *my_renderer) {
	ZeroMemory(&file_name, sizeof(file_name));
	ZeroMemory(&open_file_name, sizeof(open_file_name));
	open_file_name.lStructSize = sizeof(open_file_name);
	open_file_name.hwndOwner = NULL;
	open_file_name.lpstrFilter = "Image Files\0*.png\0";
	open_file_name.lpstrFile = file_name;
	open_file_name.nMaxFile = MAX_PATH;
	open_file_name.lpstrTitle = "Select a tile";
	open_file_name.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&open_file_name)) {
		if (total_tiles_to_draw < 128) {
			std::string _file_name = file_name;
			SDL_Rect temp_rect;
			SDL_Texture *t_tile_texture = img_c.Load_Texture(my_renderer, _file_name, temp_rect.w, temp_rect.h);
			
			Tile *tttt = new Tile(tx, ty, 48, 48, total_tiles_to_draw);
			tttt->Set_Tile_Texture(t_tile_texture);
			tttt->Set_Tile_Img_Dimensions(temp_rect.w, temp_rect.h);
			tile_textures.push_back(t_tile_texture);
			texture_rect.push_back(temp_rect);
			tile_to_select.push_back(tttt);
			total_tiles_to_draw++;
			tx += 54;
			if (total_tiles_to_draw % 8 == 0) {
				tx = 0;
				ty += 54;
			}
		}

	}
	else {
		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
		case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
		case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
		case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
		case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
		case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
		case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
		case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
		case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
		case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
		case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
		case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
		case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
		case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
		case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
		default: std::cout << "You cancelled.\n";
		}
	}
}

///Function for the Tile Selection HUD on the left hand side.
void Editor::Sel_Tile(SDL_Renderer *my_renderer, const int screen_height, int mouses_x, int mouses_y) {

	SDL_GetMouseState(&mouses_x, &mouses_y);
	for (int t = 0; t < tile_to_select.size(); t++) {
		///Set up a rect for the collision
		SDL_Rect col_box = tile_to_select[t]->Get_Tile_Rect();

		///Check if the mouse is colliding with a HUD tile
		if ( (mouses_x > col_box.x)
			&& (mouses_x < col_box.x + col_box.w)
			&& (mouses_y > col_box.y)
			&& (mouses_y < col_box.y + col_box.h)) {

			///Create new seld_tile based on our clicked tile. Seld_tile shows what tile we currently have selected.
			seld_tile = new Tile(432 / 2 - 20, screen_height - 100, 48, 48, tile_to_select[t]->Get_Tile_Ref());

			seld_tile->Set_Tile_Texture(tile_textures[tile_to_select[t]->Get_Tile_Ref()]);
			seld_tile->Set_Tile_Img_Dimensions(texture_rect[tile_to_select[t]->Get_Tile_Ref()].w, texture_rect[tile_to_select[t]->Get_Tile_Ref()].h);
			
		}
	}
}

///Function to set the selected tile while deleting the old one.
void Editor::Set_Tile(SDL_Renderer *my_renderer, int &mouses_x, int &mouses_y) {

	for (int i = 0; i < tile_map_vector.size(); i++) {

		///Set up a rect for the collision
		SDL_Rect col_box = tile_map_vector[i]->Get_Tile_Rect();

		///Check if the mouse is colliding with a tilemap tile
		if ((mouses_x > col_box.x )
			&& ((mouses_x < col_box.x + col_box.w))
			&& (mouses_y > col_box.y )
			&& ((mouses_y < col_box.y + col_box.h) )) {

			///Create a new tile object to insert into the list.
			///Updated the tile class since last time. No longer takes a renderer or an image. Significantly increased load time.
			///We still keep position, dimensions, and the tile id because we're using a vector and not an array.
			Tile *test_tiler = new Tile(col_box.x, col_box.y, 48, 48, seld_tile->Get_Tile_Ref());

			///Load the image separately. One copy of each tile image we want on start up into a vector instead of each tile loading an image
			///Load times are faster and can load a lot more tiles.
			test_tiler->Set_Tile_Texture(tile_textures[seld_tile->Get_Tile_Ref()]);

			///Use the replace algorithm to replace the tile clicked on with a new tile.
			///Can't do push_back because the tiles will be out of order. We need to insert it at the deleted tile's position in the vector.
			std::replace(tile_map_vector.begin(), tile_map_vector.end(), tile_map_vector[i], test_tiler);
		}
	}
}


void Editor::Zoom(float zoom_v) {
	zoom += zoom_v;
}

float Editor::Get_Zoom() const {
	return zoom;
}


void Editor::Render_Map(SDL_Renderer *my_renderer) {
	for (int i = 0; i < tile_map_vector.size(); i++) {
		tile_map_vector[i]->Render(my_renderer, c->Get_Cam_Rect(), zoom);
	}
}

void Editor::Render_HUD_Tiles(SDL_Renderer *my_renderer) {
	if (!tile_to_select.empty()) {
		for (int i = 0; i < tile_to_select.size(); i++) {
			tile_to_select[i]->Draw(my_renderer);
		}
	}
	seld_tile->Draw(my_renderer);
}
