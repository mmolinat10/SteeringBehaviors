#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_SimpleApp.h"
#include "SceneKinematicSeek.h"
#include "SceneKinematicFlee.h"
#include "SceneSeek.h"
#include "SceneFlee.h"
#include "SceneArrive.h"
#include "ScenePursue.h"
#include "SceneEvade.h"
#include "SceneWander.h"


using namespace std;

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new SceneKinematicSeek;
	app->setWindowTitle(curr_scene->getTitle());

	while (!quit)
	{
		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_1) //NormalSeek
			{
				delete(curr_scene);
				curr_scene = new SceneKinematicSeek;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_2) //NormalFlee
			{
				delete(curr_scene);
				curr_scene = new SceneKinematicFlee;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_3) //Seek
			{
				delete(curr_scene);
				curr_scene = new SceneSeek;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_4) //Flee
			{
				delete(curr_scene);
				curr_scene = new SceneFlee;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_5) //Arrive
			{
				delete(curr_scene);
				curr_scene = new SceneArrive;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_6) //Pursue
			{
				delete(curr_scene);
				curr_scene = new ScenePursue;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_7) //Evade
			{
				delete(curr_scene);
				curr_scene = new SceneEvade;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_8) //Wander
			{
				delete(curr_scene);
				curr_scene = new SceneWander;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if ((event.key.keysym.scancode == SDL_SCANCODE_Q) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				quit = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				app->setFullScreen();
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

	}

	return 0;
}