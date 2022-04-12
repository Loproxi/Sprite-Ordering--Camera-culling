#pragma once
#include "Render.h"



class Player
{

public:
	Player();

	~Player();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start();

	bool PreUpdate();
	// Called at the middle of the application loop
	// Processes new input and handles player movement
	bool Update();

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	bool PostUpdate();

private:

	iPoint position;

	SDL_Rect* player;

	int speed = 3;

};

