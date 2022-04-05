#pragma once
#include "App.h"
#include "Render.h"
#include <vector>

using namespace std;

class RenderObjectsManager
{
public:
	RenderObjectsManager();

	~RenderObjectsManager();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	void SortingRenderObjectsWithOrdenInLayer(/*vector<renderObject>& vectorofobjectstosort*/);

	void AddrenderObject(SDL_Texture* texture, iPoint pos, SDL_Rect* section,int layer,float ordeninlayer,bool isFlipH = false, float scale = 1.0f, float speed = 1.0f);

public:

	vector< vector<renderObject>> layers;
};

