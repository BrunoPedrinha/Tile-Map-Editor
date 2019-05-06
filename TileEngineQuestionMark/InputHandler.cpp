#include "InputHandler.h"



InputHandler::InputHandler()
{
	left_m_pressed = false;
	right_m_pressed = false;
	quit_game = false;
	backspace_pressed = false;
	enter_pressed = false;
	num_pressed = false;
}


InputHandler::~InputHandler()
{
}

void InputHandler::Update() {
	
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) quit_game = true;

		Left_Mouse_Pressed();
		Right_Mouse_Pressed();
		Key_Down_No_Repeat();
	}
	
}


void InputHandler::Left_Mouse_Pressed() {
	if(e.type == SDL_MOUSEBUTTONDOWN){
		if (e.button.button == SDL_BUTTON_LEFT) {
			left_m_pressed = true;
			right_m_pressed = false;
		}
	}
	if (e.type == SDL_MOUSEBUTTONUP) {
		if (e.button.button == SDL_BUTTON_LEFT) {
			left_m_pressed = false;
			right_m_pressed = false;
		}
	}
}

void InputHandler::Right_Mouse_Pressed() {
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		if (e.button.button == SDL_BUTTON_RIGHT) {
			left_m_pressed = false;
			right_m_pressed = true;
		}
	}
	if (e.type == SDL_MOUSEBUTTONUP) {
		if (e.button.button == SDL_BUTTON_RIGHT) {
			left_m_pressed = false;
			right_m_pressed = false;
		}
	}
}

void InputHandler::Get_Input() {
	
	if (e.key.keysym.scancode >= 30 && e.key.keysym.scancode <= 39) {
		my_kc = e.key.keysym.sym;
		num_pressed = true;
	}
	else if (e.key.keysym.sym == SDLK_BACKSPACE)
		Set_Backspace_Pressed(true);

	else if (e.key.keysym.sym == SDLK_RETURN)
		Set_Enter_Pressed(true);
}

void InputHandler::Key_Down_No_Repeat() {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		Get_Input();
	}
}