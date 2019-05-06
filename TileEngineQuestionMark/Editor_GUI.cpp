#include "Editor_GUI.h"



Editor_GUI::Editor_GUI(){
	
	TTF_Init();
	
	int img_flags = IMG_INIT_PNG;
	if (IMG_Init(img_flags) != img_flags) std::cout << "IMG INIT ERROR" << std::endl;
	text_box_width = "10";
	text_box_height = "10";

	black_box = new Sprite(Get_Renderer(), "Sprites/UI/blackbg.png", 0, 0, 432, Get_Window_Height());
	///the text that says Selected Tile:
	sel_tile_txt = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 30, "Selected Tile:", c, 40, Get_Window_Height() - 80);

	///the buttons for the new map, save map, load map and the text
	button1 = new Sprite(Get_Renderer(), "Sprites/UI/button.png", 20, Get_Window_Height() - 175, 100, 50);
	button2 = new Sprite(Get_Renderer(), "Sprites/UI/button.png", 165, Get_Window_Height() - 175, 100, 50);
	button3 = new Sprite(Get_Renderer(), "Sprites/UI/button.png", 312, Get_Window_Height() - 175, 100, 50);
	button4 = new Sprite(Get_Renderer(), "Sprites/UI/button.png", 312, Get_Window_Height() - 100, 100, 50);

	input_width_box = new Sprite(Get_Renderer(), "Sprites/UI/button1.png", 20, Get_Window_Height() - 220, 100, 30);
	input_height_box = new Sprite(Get_Renderer(), "Sprites/UI/button1.png", 220, Get_Window_Height() - 220, 100, 30);
	width_text = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 30, text_box_width, c, (input_width_box->pos_rect.x + input_width_box->pos_rect.w - 32), input_width_box->pos_rect.y + 8);
	height_text = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 30, text_box_height, c, (input_height_box->pos_rect.x + input_height_box->pos_rect.w - 32), input_height_box->pos_rect.y + 8);

	width_label = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 30, "Width", c, (input_width_box->pos_rect.x + input_width_box->pos_rect.w) + 10, input_width_box->pos_rect.y + 8);
	height_label = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 30, "Height", c, (input_height_box->pos_rect.x + input_height_box->pos_rect.w) + 10, input_height_box->pos_rect.y + 8);

	new_map = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 35, "New Map", c, button1->pos_rect.x + 5, button1->pos_rect.y + 12);
	load_map = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 30, "Load Map", c, button2->pos_rect.x + 6, button2->pos_rect.y + 12);
	save_map = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 30, "Save Map", c, button3->pos_rect.x + 6, button3->pos_rect.y + 12);
	import_text = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 30, "Import", c, button4->pos_rect.x + 18, button4->pos_rect.y + 6);
	tile_text = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 30, "Tile", c, button4->pos_rect.x + 28, button4->pos_rect.y + 28);
	
	ih = new InputHandler();

	m_x = m_y = 0;

}


Editor_GUI::~Editor_GUI(){
	delete black_box;
	delete sel_tile_txt;
	delete button1;
	delete button2;
	delete button3;
	delete button4;
	delete input_width_box;
	delete input_height_box;
	delete width_text;
	delete height_text;
	delete width_label;
	delete height_label;
	delete new_map;
	delete load_map;
	delete save_map;
	delete import_text;
	delete tile_text;
	Editor::~Editor();
}


void Editor_GUI::Draw_UI() {

	Render_Map(Get_Renderer());
	black_box->Draw(Get_Renderer());
	Render_HUD_Tiles(Get_Renderer());
	
	sel_tile_txt->Render(Get_Renderer());
	button1->Draw(Get_Renderer());
	button2->Draw(Get_Renderer());
	button3->Draw(Get_Renderer());
	button4->Draw(Get_Renderer());
	width_label->Render(Get_Renderer());
	height_label->Render(Get_Renderer());

	input_width_box->Draw(Get_Renderer());
	input_height_box->Draw(Get_Renderer());

	if (input_width_b || input_height_b) {
		text_cursor->Render(Get_Renderer());

	}

	width_text->Render(Get_Renderer());
	height_text->Render(Get_Renderer());


	new_map->Render(Get_Renderer());
	load_map->Render(Get_Renderer());
	save_map->Render(Get_Renderer());
	import_text->Render(Get_Renderer());
	tile_text->Render(Get_Renderer());

	
}



void Editor_GUI::Update(bool &game_loop) {

	ih->Update();

	if (ih->Get_Quit_Game())
		game_loop = false;
	

	if (black_box->Collisionslol(m_x, m_y)){
		if (ih->Get_Mouse_L_Press()){
			if (button1->Collisionslol(m_x, m_y))
				New_Map(Get_Renderer());

			else if (button2->Collisionslol(m_x, m_y))
				Load_Map(Get_Renderer());

			else if (button3->Collisionslol(m_x, m_y))
				Save_Map();

			else if (button4->Collisionslol(m_x, m_y))
				Import_Tile(Get_Renderer());

			else if (input_width_box->Collisionslol(m_x, m_y)) {
				input_width_b = true;
			}
			else if (!input_width_box->Collisionslol(m_x, m_y)) {
				delete text_cursor;
				text_cursor = NULL;
				input_width_b = false;
			}

			if (input_height_box->Collisionslol(m_x, m_y)) {
				input_height_b = true;
			}
			else if (!input_height_box->Collisionslol(m_x, m_y)) {
				delete text_cursor;
				text_cursor = NULL;
				input_height_b = false;
			}
		}
		if (ih->Get_Mouse_R_Press()) {
			Sel_Tile(Get_Renderer(), Get_Window_Height(), m_x, m_y);
		}
	}
	else {
		if (ih->Get_Mouse_L_Press()) {
			Set_Tile(Get_Renderer(), m_x, m_y);
		}
	}


	/*if (e.key.keysym.sym == SDLK_KP_MINUS) {
		if (Get_Zoom() > 0.1f)
			Zoom(-0.1f);
	}
	if (e.key.keysym.sym == SDLK_KP_PLUS)
		Zoom(0.1f);*/

	if (input_width_b) {

			if (ih->Get_Num_Pressed()) {
				text_box_width += ih->Return_KC();
				int _width_holder;
				if (text_box_width.length() == 1) _width_holder = (width_text->pos_rect.w) - 5;
				else _width_holder = (width_text->pos_rect.w) + 5;
				delete width_text;
				width_text = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf",
					30, text_box_width, c, (input_width_box->pos_rect.x + input_width_box->pos_rect.w - 15) - _width_holder, input_width_box->pos_rect.y + 8);
				ih->Set_Num_Pressed(false);
			}

			else if (ih->Get_Backspace_Pressed()) {
				if (text_box_width.length() > 0)
					text_box_width = text_box_width.substr(0, text_box_width.length() - 1);
				else ih->Set_Backspace_Pressed(false);
				int _width_holder;
				if (text_box_width.length() == 0) _width_holder = (width_text->pos_rect.w) - 5;
				else _width_holder = (width_text->pos_rect.w) - 15;
				delete width_text;
				width_text = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf",
					30, text_box_width, c, 
					(input_width_box->pos_rect.x + input_width_box->pos_rect.w - 15) - _width_holder, 
					input_width_box->pos_rect.y + 8);
				ih->Set_Backspace_Pressed(false);
			}
			if (ih->Get_Enter_Pressed()) {
				int val = atoi(text_box_width.c_str());
				Set_Map_Width(val);
				delete text_cursor;
				text_cursor = NULL;
				input_width_b = false;
				ih->Set_Enter_Pressed(false);
			}
	}
	else if (input_height_b) {
		
			if (ih->Get_Num_Pressed()){
				text_box_height += ih->Return_KC();
				int _height_holder;
				if (text_box_height.length() == 1) _height_holder = (height_text->pos_rect.w) - 5;
				else  _height_holder = (height_text->pos_rect.w) + 5;
				delete height_text;
				height_text = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 
					30, text_box_height, c,
					(input_height_box->pos_rect.x + input_height_box->pos_rect.w - 15) - _height_holder,
					input_height_box->pos_rect.y + 8);
				ih->Set_Num_Pressed(false);
			}
			else if (ih->Get_Enter_Pressed()) {
				int val = atoi(text_box_height.c_str());
				Set_Map_Height(val);

				delete text_cursor;
				text_cursor = NULL;
				input_height_b = false;
				ih->Set_Enter_Pressed(false);
			}
			else if (ih->Get_Backspace_Pressed()) {
				if (text_box_height.length() > 0)
					text_box_height = text_box_height.substr(0, text_box_height.length() - 1);
				
				int _height_holder;
				if (text_box_height.length() == 0) _height_holder = (height_text->pos_rect.w) - 5;
				else  _height_holder = (height_text->pos_rect.w) - 15;
				delete height_text;
				height_text = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf",
					30, text_box_height, c, (input_height_box->pos_rect.x + input_height_box->pos_rect.w - 15) - _height_holder, input_height_box->pos_rect.y + 8);
				ih->Set_Backspace_Pressed(false);
			}
	}
	SDL_GetMouseState(&m_x, &m_y);
	Editor::Update(m_x, m_y);


	if (input_width_b) {
		if (text_cursor == NULL) {
			text_cursor = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 30, "|", c, input_width_box->pos_rect.x + input_width_box->pos_rect.w - 15, input_width_box->pos_rect.y + 8);
		}
		if (_delay + 1000 < SDL_GetTicks()) {
			text_cursor->Alive = false;
			_delay = SDL_GetTicks();
		}
		else if (_delay + 300 < SDL_GetTicks()) {
			text_cursor->Alive = true;
		}
	}
	else if (input_height_b) {
		if (text_cursor == NULL) {
			text_cursor = new GameText(Get_Renderer(), "Fonts/coders_crux.ttf", 30, "|", c, input_height_box->pos_rect.x + input_height_box->pos_rect.w - 15, input_height_box->pos_rect.y + 8);
		}
		if (_delay + 1000 < SDL_GetTicks()) {
			text_cursor->Alive = false;
			_delay = SDL_GetTicks();
		}
		else if (_delay + 300 < SDL_GetTicks()) {
			text_cursor->Alive = true;
		}
	}
}