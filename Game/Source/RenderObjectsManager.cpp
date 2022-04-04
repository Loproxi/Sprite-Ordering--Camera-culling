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
	return true;
}

void RenderObjectsManager::SortingRenderObjectsWithOrdenInLayer(vector<renderObject>& listofobjectstosort)
{
}

void RenderObjectsManager::AddrenderObject(SDL_Texture* texture, iPoint pos, SDL_Rect* section, bool isFlipH, float scale, float speed)
{
	renderObject renderobject;

	renderobject.texture = texture;
	renderobject.section = section;

	renderobject.renderRect.x = (int)(app->render->camera.x * speed) + pos.x * scale;
	renderobject.renderRect.y = (int)(app->render->camera.y * speed) + pos.y * scale;

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

	renderObjects.push_back(renderobject);
}
