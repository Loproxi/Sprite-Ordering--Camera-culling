#include "RenderObjectsManager.h"


RenderObjectsManager::RenderObjectsManager()
{
}

RenderObjectsManager::~RenderObjectsManager()
{
}

bool RenderObjectsManager::Start()
{
	return true;
}

bool RenderObjectsManager::PreUpdate()
{


	return true;
}

bool RenderObjectsManager::Update(float dt)
{
	return true;
}

bool RenderObjectsManager::PostUpdate()
{

	//Hacer sorting

	// for each 
	//if is in camera
	//and draw function

	//Clear vector
	return true;
}

void RenderObjectsManager::SortingRenderObjectsWithOrdenInLayer(vector<renderObject>& vectorofobjectstosort)
{
	
	int small;
	int length = vectorofobjectstosort.size();

	for (int i = 0; i < length - 1; i++)
	{
		small = i;
		for (int j = i + 1 ; j < length; j++)
		{
			if (vectorofobjectstosort[j].Ordeninlayer < vectorofobjectstosort[small].Ordeninlayer)
			{
				small = j;
			}
		}
		swap(vectorofobjectstosort[i], vectorofobjectstosort[small]);

	}
	
}

void RenderObjectsManager::AddrenderObject(SDL_Texture* texture, iPoint pos, SDL_Rect* section, int layer, float ordeninlayer, bool isFlipH, float scale, float speed)
{
	renderObject renderobject;

	renderobject.texture = texture;
	renderobject.section = section;
	renderobject.Ordeninlayer = ordeninlayer;
	renderobject.speed = speed;
	renderobject.renderRect.x = (int)(app->render->camera.x * speed) + pos.x * scale;
	renderobject.renderRect.y = (int)(app->render->camera.y * speed) + pos.y * scale;

	if (layer == 3) renderobject.speed = 0;

	if (section != nullptr)
	{
		renderobject.renderRect.w = section->w;
		renderobject.renderRect.h = section->h;
	}
	else
	{
		// Get the texture size 
		SDL_QueryTexture(texture, nullptr, nullptr, &renderobject.renderRect.w, &renderobject.renderRect.h);
	}

	renderobject.renderRect.w *= scale;
	renderobject.renderRect.h *= scale;

	if (isFlipH == false)
	{
		renderobject.flip = SDL_FLIP_VERTICAL;
	}
	else
	{
		renderobject.flip = SDL_FLIP_HORIZONTAL;
	}

	layers[layer].push_back(renderobject);
}
