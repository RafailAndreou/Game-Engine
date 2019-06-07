#pragma once
#include "pch.h"
#include<iostream>
#include "SDL.h"
#include "SDL_TTF.h"
#include <Windows.h>
#include <ShObjIdl.h>

extern SDL_Window * window;
extern SDL_Color MessageColor;
extern SDL_Surface* surfaceMessage;
extern SDL_Texture* Message;
extern SDL_Rect * MessageRect[5];
extern int i;
extern Uint8 r, g, b;
extern int CheckColor;
extern int counter;

extern int WindowWidth;
extern int WindowHeight;

void ShowText();

class Rect {
	SDL_Renderer * rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE); //Create Renderer
	SDL_Rect rect[5]; // Buttons
	SDL_Surface * surface = SDL_GetWindowSurface(window); //Create Surface That we will render everything
	SDL_Texture * texture = SDL_CreateTextureFromSurface(rend, surface); // Create a texture from the surface because is faster
	SDL_Rect MessageRect; //Text  on button

public:
	Rect(int x, int y, int h, int w) {
		for (int i = 0; i < 5;i++) {
			if (i == 0) {
				rect[i].x = x; // x position of first button
			}
			else {
				rect[i].x = x + + w + rect[i - 1].x ; // x position of other buttons
			}

			rect[i].y = y; // y position of button
			rect[i].h = h ; // height of button
			rect[i].w = w ; // width of button
			SDL_SetRenderDrawColor(rend, 60, 60, 60, 0); // Background Color
			SDL_RenderClear(rend); //Show Background Color
		}
	}

	void MouseHover() {
		int mX, mY; // Mouse x And y Position
		bool inhover = true;
		SDL_Event e;
		while (inhover) {
			SDL_PumpEvents();
			SDL_GetMouseState(&mX, &mY); //Get Mouse x And y Position
			if ((mX > rect[i].x && mX < rect[i].x + rect[i].w) && (mY > rect[i].y && mY < rect[i].y + rect[i].h)) { // If Mouse x And y Position Is On Rectangle
				while (SDL_PollEvent(&e)) //while events happens
					if (e.type == SDL_MOUSEBUTTONDOWN) { // If the button= is clicked
						std::cout << "You pressed button " << i + 1 << std::endl; // Button Action
					}

				// Set r,g,b values So The Color Is Dark Grey
				if (r + g + b != 270) {
					r = 90;
					g = 90;
					b = 90;
					SDL_SetRenderDrawColor(rend, r, g, b, 255);//Set Color 
					SDL_RenderFillRect(rend, &rect[i]);//Fill the rectangle's color
					SDL_RenderPresent(rend);//Show new rectangle
					ShowText(); // Show Text

				}
			}
			else {
				if (r + g + b != 0 || counter <= 5) { // If The Button Was Dark Grey 
					//Set r,g,b Values
					r = 0;
					g = 0;
					b = 0;
					SDL_SetRenderDrawColor(rend, r, g, b, 255); // Set Renderer Color
					SDL_RenderFillRect(rend, &rect[i]); // Fill Renderer Color
					SDL_RenderPresent(rend); // Show Renderer (The New Color)
					counter++;
					ShowText(); // Show Text
				}
				inhover = false;
				if (i == 5)	i = 0;
				else i++;
			}
		}
	}

	void Menu() {
		SDL_Rect Menu;
		Menu.h = 30;
		Menu.w = Size();
		Menu.x = 0;
		Menu.y = 0;
		SDL_SetRenderDrawColor(rend, 5, 5, 5, 255);
		SDL_RenderFillRect(rend, &Menu);
		SDL_RenderPresent(rend);
	}

	int Size() {
		int * Height = &WindowHeight;
		int * Width = &WindowWidth;
		int CheckHeight = WindowHeight;
		int CheckWidth = WindowWidth;
		SDL_GetWindowSize(window, Width, Height);
		if (WindowHeight != CheckHeight || WindowWidth != CheckWidth) {
			r = 60;
			g = 60;
			b = 60;
			SDL_SetRenderDrawColor(rend, r, g, b, 0);
			SDL_RenderClear(rend);
			Menu();
		}
		return *Width;
	}



	void ShowText() {
		TTF_Font* Sans = TTF_OpenFont("Segoeui.ttf", 100); // Initialize Text
		SDL_Color MessageColor = { 255, 255, 255 }; // Text Color
		SDL_Surface* surfaceMessage[5];
		SDL_Texture* Message[5];
		SDL_Rect MessageRect[5]; // Create Rect
		if (CheckColor != r + g + b || counter <= 5) {
			CheckColor = r + g + b;
			for (int i = 0; i < 5; i++) {
				MessageRect[i].y = 8;  // X Position Of Message
				MessageRect[i].w = 55; // Width Of Message
				MessageRect[i].h = 15; // Height Of Message
				switch (i) {// Initialize Text
				case 0:
						surfaceMessage[i] = TTF_RenderText_Solid(Sans, "Button 1", MessageColor);
						break;
				case 1:
					surfaceMessage[i] = TTF_RenderText_Solid(Sans, "Button 2", MessageColor);
					break;
				case 2:
					surfaceMessage[i] = TTF_RenderText_Solid(Sans, "Button 3", MessageColor);
					break;
				case 3:
					surfaceMessage[i] = TTF_RenderText_Solid(Sans, "Button 4", MessageColor);
					break;
				case 4:
					surfaceMessage[i] = TTF_RenderText_Solid(Sans, "Button 5", MessageColor);
					break;
				}

				if (i == 0) {
					Message[i] = SDL_CreateTextureFromSurface(rend, surfaceMessage[i]); // Create Texture From Surface
					MessageRect[i].x = 15; // x position of message 
					SDL_RenderCopy(rend, Message[i], NULL, &MessageRect[i]);// Import Whole Message on Texture
					SDL_RenderPresent(rend); // Show Message
				}
				else
				{
					Message[i] = SDL_CreateTextureFromSurface(rend, surfaceMessage[i]); // Create Texture From Surface
					MessageRect[i].x = MessageRect[i - 1].x + 80;
					SDL_RenderCopy(rend, Message[i], NULL, &MessageRect[i]);// Import Whole Message on Texture
					SDL_RenderPresent(rend); // Show Message
				}
			}
		}
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
