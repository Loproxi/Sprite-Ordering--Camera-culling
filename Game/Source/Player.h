#pragma once
#include "Render.h"
#include "Animation.h"


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

	bool CleanUp();

private:

	iPoint position;

	SDL_Rect player;

	SDL_Rect* animsections = nullptr;

	int speed = 3;

	SDL_Texture* tex = nullptr;

	Animation idleAnim;

	Animation rightAnim;

	Animation leftAnim;

	Animation* currentAnim = nullptr;

	bool isflip = false;
};

