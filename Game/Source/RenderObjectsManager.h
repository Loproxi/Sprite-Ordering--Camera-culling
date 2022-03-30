#pragma once
#include "App.h"
#include "Render.h"
#include <vector>

using namespace std;

class RenderObjectsManager
{

	RenderObjectsManager();

	~RenderObjectsManager();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	void AddrenderObject(SDL_Texture* texture, iPoint pos, SDL_Rect* section, bool isFlipH = false, float scale = 1.0f, float speed = 3.0f);

public:

	vector<renderObject> renderObjects;
	
};

