#include "SDL_SimpleApp.h"

using namespace std;

SDL_SimpleApp * SDL_SimpleApp::s_pInstance = 0;

SDL_SimpleApp * SDL_SimpleApp::Instance() {
	if (s_pInstance == 0) {
		s_pInstance = new SDL_SimpleApp();
	}
	return s_pInstance;
}

SDL_SimpleApp::SDL_SimpleApp() {
	win_fullscreen = false;
	win_width = 1280;
	win_height = 768;

	SDL_Init(SDL_INIT_VIDEO);

	if ((IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) != IMG_INIT_PNG) {
		cout << "IMG_Init: Failed to init required img support!" << endl;
		cout << "IMG_Init: " << IMG_GetError() << endl;
	}

	window = SDL_CreateWindow("SDL Steering Behaviors",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_width, win_height, 0);

	if (win_fullscreen)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
	SDL_RenderClear(renderer);

	last_update = (float)SDL_GetTicks();
}

SDL_SimpleApp::~SDL_SimpleApp() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

SDL_Event SDL_SimpleApp::run(Scene *scene) {
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT) {
		return event;
	}

	float dtime = (float)(SDL_GetTicks() - last_update) / 1000.0f;
	last_update = (float)SDL_GetTicks();
	SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
	SDL_RenderClear(renderer);
	if (bgImage)SDL_RenderCopy(renderer, bgImage, NULL, NULL);
	scene->update(dtime,&event);
	scene->draw();
	SDL_RenderPresent(renderer);
	return event;
}

Vector2D SDL_SimpleApp::getWinSize() {
	return Vector2D((float)win_width, (float)win_height);
}

void SDL_SimpleApp::setWindowTitle(const char *title) {
	SDL_SetWindowTitle(window, title);
}

void SDL_SimpleApp::setBackgroundColor(SDL_Color color) {
	bg_color = color;
}

void SDL_SimpleApp::setBackgroundImage(char* filename) {
	SDL_Surface *image = IMG_Load(filename);

	bgImage = SDL_CreateTextureFromSurface(renderer, image);
	
	if (image)
		SDL_FreeSurface(image);
}

void SDL_SimpleApp::setFullScreen() {
	win_fullscreen = !win_fullscreen;
	if (win_fullscreen)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	else {
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowDisplayMode(window, NULL);
	}
}