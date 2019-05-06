#pragma once
#include <SDL.h>
#include "Editor.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void Update();

	std::string Return_KC() { return my_kc; }

	bool Get_Mouse_R_Press() { return right_m_pressed; }
	bool Get_Mouse_L_Press() { return left_m_pressed; }
	bool Get_Quit_Game() { return quit_game; }
	bool Get_Backspace_Pressed() { return backspace_pressed; }
	bool Get_Enter_Pressed() { return enter_pressed; }
	

	int Get_Num_Pressed() { return num_pressed; }

	void Set_Num_Pressed(bool value) { num_pressed = value; }
	void Set_Backspace_Pressed(bool value) { backspace_pressed = value; }
	void Set_Enter_Pressed(bool value) { enter_pressed = value; }

private:
	SDL_Event e;
	void Left_Mouse_Pressed();
	void Right_Mouse_Pressed();
	void Get_Input();
	void Key_Down_No_Repeat();
	std::string my_kc;
	bool right_m_pressed, left_m_pressed, quit_game, backspace_pressed, enter_pressed, num_pressed;
};