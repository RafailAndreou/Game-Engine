#include "pch.h"
#include<iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include "Buttons.hpp"
//Initialize Vars
SDL_Window * window = nullptr;
SDL_Color MessageColor;
SDL_Surface* surfaceMessage = nullptr;
SDL_Texture* Message = nullptr;
SDL_Rect * MessageRectPtr = nullptr;
int i = 0;
Uint8 r = 60, g = 60, b = 60;
int counter = 0;

const int Window_Width = 500;
const int Window_Height = 300;

//Initialize TTF SDL and create window
void Init() {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Window_Width, Window_Height,SDL_WINDOW_RESIZABLE);
	if (window == NULL) std::cout << SDL_GetError << std::endl;
}


int main(int argc, char *argv[]) {
	Init(); 
	SDL_Event  event;
	Rect Button(1, 0, 20, 80);
	Button.OutlineDraw(); //Call OutlineDraw()
	bool running = true; 
	while (running == true) {
		Button.MouseHover(); //Call MouseHover() 
		while (SDL_PollEvent(&event)) { // If Events Happen
			if (event.type == SDL_QUIT) { // If The Event is Quit
				running = false; // Get Out Of The Loop
			}
		}
		Button.TTF(); // Show Text
		if (i == 5)	i = 0;
		else i++;
	}
	Button.Destroy();// Call Destroy
	return 0;
}