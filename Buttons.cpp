#include "pch.h"
#include<iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"


SDL_Window * window = nullptr;

const int Window_Width = 500;
const int Window_Height = 300;

void Init() {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Window_Width, Window_Height,NULL);
	if (window == NULL) std::cout << SDL_GetError << std::endl;	
}



class Rect {
	SDL_Renderer * rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Rect outline[5];
	SDL_Rect rect[5];
	SDL_Surface * surface = SDL_GetWindowSurface(window);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(rend, surface);
public:
	Rect(int x, int y, int h, int w) {
		for (int i = 0; i < 5;i++) {
			if (i == 0) {
				outline[i].x = x + 2;
				rect[i].x = x + 5;
			}
			else {
				outline[i].x = x + 10 + w + outline[i - 1].x + 2;
				rect[i].x = x + 10 + w + outline[i - 1].x + 5;
			}
			outline[i].y = y + 2;
			outline[i].h = h + 2;
			outline[i].w = w + 2;

			rect[i].y = y + 5;
			rect[i].h = h - 5;
			rect[i].w = w - 5;
		}
	}
	void draw() {
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_RenderClear(rend);
		for (int i = 0; i < 5;i++) {
			SDL_SetRenderDrawColor(rend, 40, 40, 40, 255);
			SDL_RenderCopy(rend, texture, NULL, &outline[i]);
			SDL_SetRenderDrawColor(rend, 200, 200, 200, 255);
			SDL_RenderCopy(rend, texture, NULL, &outline[i]);
			SDL_RenderPresent(rend);
		}
	}
	void Mouse_Hover() {
		int mX, mY;
		SDL_GetMouseState(&mX, &mY);
		for (int i = 0;i < 5;i++) {
			if ((mX > outline[i].x && mX < outline[i].x + outline[i].w) && (mY > outline[i].y && mY < outline[i].y + outline[i].h)) {
				SDL_SetRenderDrawColor(rend, 60, 60, 60, 255);
				SDL_RenderCopy(rend, texture, NULL, &rect[i]);
				SDL_RenderFillRect(rend, &rect[i]);
				SDL_RenderPresent(rend);
			}
			else {
				SDL_SetRenderDrawColor(rend, 200, 200, 200, 255);
				SDL_RenderCopy(rend, texture, NULL, &rect[i]);
				SDL_RenderFillRect(rend, &rect[i]);
				SDL_RenderPresent(rend);
			}
		}
	}
	
	
	void TTF() {
		if (TTF_Init() < 0) std::cout << TTF_GetError() << std::endl;
	}

	void Destroy() {
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(rend);
		TTF_Quit();
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
};

int main(int argc, char *argv[]) {
	Init();
	SDL_Event  event;
	Rect Button(1, 0, 20, 80);
	Button.draw();
	bool running = true;
	while (running == true) {
		Button.Mouse_Hover();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
	}
	TTF_GetError();
	Button.Destroy();
	return 0;
}
