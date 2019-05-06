#pragma once
#include "GameText.h"
#include "Sprite.h"
#include "Editor.h"
#include "InputHandler.h"

class Editor_GUI : public Editor
{
public:
	Editor_GUI();
	~Editor_GUI();
	void Draw_UI();
	void Update(bool &game_loop);




private:
	InputHandler *ih;

	SDL_Color c = { 255, 255, 255, 255 };

	GameText *text_cursor, *width_text, *height_text, *height_label, *width_label,
		*sel_tile_txt, *new_map, *load_map, *save_map, *import_text, *tile_text;

	Sprite *black_box, *input_width_box, *input_height_box, *button1, *button2, *button3, *button4;
	std::string text_box_width, text_box_height;
	bool input_width_b = false, input_height_b = false;
	int m_x, m_y;
	float _delay = 0;
};


