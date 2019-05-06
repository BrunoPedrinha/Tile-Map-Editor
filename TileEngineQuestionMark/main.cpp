#include "Editor_GUI.h"

Editor_GUI *egui;

///25, 26x2, 27

int main(int argc, char ** argv)
{
	bool game_running = true;
	egui = new Editor_GUI();
	
	while (game_running) {
		egui->Update(game_running);

		SDL_RenderClear(egui->Get_Renderer());
		egui->Draw_UI();
		SDL_RenderPresent(egui->Get_Renderer());
	}
	egui->~Editor_GUI();
	SDL_Quit();
	return 0;
}








