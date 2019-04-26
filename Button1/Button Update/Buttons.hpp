#pragma once
#include "pch.h"
#include<iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"

extern SDL_Window * window;
extern SDL_Color MessageColor;
extern SDL_Surface* surfaceMessage;
extern SDL_Texture* Message;
extern SDL_Rect * MessageRectPtr;
extern int i;
extern Uint8 r, g, b;
extern int counter;

extern int Window_Width;
extern int Window_Height;

void TTF();

class Rect {
	SDL_Renderer * rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //Create Renderer
	SDL_Rect outline[5]; //Outline of buttons
	SDL_Rect rect[5]; // Buttons
	SDL_Surface * surface = SDL_GetWindowSurface(window); //Create Surface That we will render everything
	SDL_Texture * texture = SDL_CreateTextureFromSurface(rend, surface); // Create a texture from the surface because is faster
	SDL_Rect MessageRect; //Text  on button

public:
	Rect(int x, int y, int h, int w) {
		for (int i = 0; i < 5;i++) {
			if (i == 0) {
				outline[i].x = x + 2; // x position of first outline
				rect[i].x = x + 5; // x position of first button
			}
			else {
				outline[i].x = x + 10 + w + outline[i - 1].x + 2; // x position of other outlines
				rect[i].x = x + 10 + w + outline[i - 1].x + 5; // x position of other buttons
			}
			outline[i].y = y + 2; // y position of outline
			outline[i].h = h + 2; // height of outline
			outline[i].w = w + 2;  // width of outline

			rect[i].y = y + 5; // y position of button
			rect[i].h = h - 5; // height of button
			rect[i].w = w - 5; // width of button
			SDL_SetRenderDrawColor(rend, 255, 255, 255, 0); // Background Color
			SDL_RenderClear(rend); //Show Background Color
		}
	}

	void Size() {
		int * Height = &Window_Height;
		int * Width = &Window_Width;
		int Check_Height = Window_Height;
		int Check_Width = Window_Width;
		SDL_GetWindowSize(window, Width, Height);
		if (Window_Height != Check_Height || Window_Width != Check_Width) {
			SDL_SetRenderDrawColor(rend, 255, 255, 255,0);
			SDL_RenderClear(rend);
		}
	}

	void OutlineDraw() {
		for (int i = 0; i < 5;i++) {
			SDL_SetRenderDrawColor(rend, 200, 200, 200, 255);//Set Outline Color
			SDL_RenderCopy(rend, texture, NULL, &outline[i]); //Import Outline Color
			SDL_RenderCopy(rend, Message, NULL, &MessageRect); //Import Message Color
		}
	}

	void MouseHover() {
		int mX, mY; // Mouse x And y Position
		bool inhover = true;
		SDL_Event e;
		while (inhover) {
			SDL_PumpEvents();
			SDL_GetMouseState(&mX, &mY); //Get Mouse x And y Position
			if ((mX > outline[i].x && mX < outline[i].x + outline[i].w) && (mY > outline[i].y && mY < outline[i].y + outline[i].h)) { // If Mouse x And y Position Is On Rectangle
				while (SDL_PollEvent(&e)) //while events happens
					if (e.type == SDL_MOUSEBUTTONDOWN) { // If the button= is clicked
						std::cout << "You pressed button " << i + 1 << std::endl; // Button Action
					}

				// Set r,g,b values So The Color Is Dark Grey
				if (r + g + b != 180) {
					r = 60;
					g = 60;
					b = 60;
					SDL_SetRenderDrawColor(rend, r, g, b, 255);//Set Color 
					SDL_RenderFillRect(rend, &rect[i]);//Fill the rectangle the color
					SDL_RenderPresent(rend);//Show new rectangle
					TTF(); // Show Text

				}
			}
			else {
				if (r + g + b != 600 || counter <= 5) { // If The Button Was Dark Grey 
					//Set r,g,b Values
					r = 200;
					g = 200;
					b = 200;
					SDL_SetRenderDrawColor(rend, r, g, b, 255); // Set Renderer Color
					SDL_RenderFillRect(rend, &rect[i]); // Fill Renderer Color
					SDL_RenderPresent(rend); // Show Renderer (The New Color)
					counter++;
					TTF(); // Show Text
				}
				inhover = false;
				if (i == 5)	i = 0;
				else i++;
			}
		}
	}
	
	void TTF(){
		TTF_Font * Sans = TTF_OpenFont("Segoeui.ttf", 50); // Initialize Text
		SDL_Color MessageColor = { 0, 0, 0 }; // Text Color
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Worked", MessageColor); // Initialize Text s
		SDL_Texture* Message = SDL_CreateTextureFromSurface(rend, surfaceMessage); // Create Texture From Surface

		SDL_Rect MessageRect; // Create Rect
		MessageRect.x = 9; // x position of message 
		MessageRect.y = 4;  // X Position Of Message
		MessageRect.w = 67; // Width Of Message
		MessageRect.h = 15; // Height Of Message
		SDL_RenderCopy(rend, Message, NULL, &MessageRect);// Import Whole Message on Texture
		SDL_RenderPresent(rend); // Show Message
		TTF_CloseFont(Sans);
	}

	void Destroy() { // Terminate Everything
		SDL_FreeSurface(surface);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(texture);
		SDL_DestroyTexture(Message);
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(window);
		TTF_Quit();
		SDL_Quit();
	}
};