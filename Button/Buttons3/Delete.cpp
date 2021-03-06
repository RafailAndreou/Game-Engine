#include "pch.h"
#include<iostream>
#include "SDL.h"
#include "SDL_TTF.h"
#include "Buttons.hpp"
#include <Windows.h>
#include <ShObjIdl.h>



//Initialize Vars
SDL_Window * window = nullptr;
SDL_Color MessageColor;
SDL_Surface* surfaceMessage = nullptr;
SDL_Texture* Message = nullptr;
SDL_Rect * MessageRectPtr = nullptr;
int i = 0;
Uint8 r = 60, g = 60, b = 60;
int  CheckColor = 0;
int counter = 0;

int WindowWidth = 400;
int WindowHeight = 300;

//Initialize TTF SDL and create window
void Init() {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight,SDL_WINDOW_RESIZABLE);
	if (window == NULL) std::cout << SDL_GetError << std::endl;
}



int main(int argc, char *argv[]) {
	Init(); 
	SDL_Event  event;
	Rect Button(0, 0, 30, 80);
	Button.Menu();
	bool running = true;
	while (running == true) {
		Button.MouseHover(); //Call MouseHover() 
		while (SDL_PollEvent(&event)) { // If Events Happen
			if (event.type == SDL_QUIT) { // If The Event is Quit
				running = false; // Get Out Of The Loop
			}
		}
		Button.Size();
		Button.ShowText(); // Call ShowText()
	}

	Button.Destroy();
	return 0;
}
