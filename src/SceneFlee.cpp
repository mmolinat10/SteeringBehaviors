#include "SceneFlee.h"

using namespace std;

SceneFlee::SceneFlee()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/isaac.png", 3);
	agents.push_back(agent);
	Target *target = new Target;
	target->loadSpriteTexture("../res/ghost.png", 24);
	targets.push_back(target);
}

SceneFlee::~SceneFlee()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	for (int i = 0; i < (int)targets.size(); i++)
	{
		delete targets[i];
	}
}

void SceneFlee::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			targets[0]->setPosition(Vector2D((float)(event->button.x), (float)(event->button.y)));
			agents[0]->setTarget(targets[0]->getPosition());
		}
		break;
	default:
		break;
	}
	Vector2D steering_force = agents[0]->Behavior()->Flee(agents[0],agents[0]->getTarget(),dtime);
	agents[0]->update(steering_force, dtime, event);
	targets[0]->update(dtime, event);
}

void SceneFlee::draw()
{
	targets[0]->draw();
	agents[0]->draw();
}

const char* SceneFlee::getTitle()
{
	return "SDL Steering Behaviors :: Flee Demo";
}