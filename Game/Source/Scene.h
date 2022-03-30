#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"


//class GuiControl;

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Define multiple Gui Event methods
	//bool OnGuiMouseClickEvent(GuiControl* control);

private:

	SDL_Texture* img;

	SDL_Texture* backgroundmap;

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager


};

#endif // __SCENE_H__