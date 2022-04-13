#include "App.h"
#include "Window.h"
#include "Render.h"
#include "Defs.h"
#include "Log.h"

#define VSYNC true
#define MAX_LAYERS 3

Render::Render() : Module()
{
	name.Create("renderer");
	background.r = 0;
	background.g = 0;
	background.b = 0;
	background.a = 0;
}

// Destructor
Render::~Render()
{}

// Called before render is available
bool Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");
	bool ret = true;

	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if(config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(app->win->window, -1, flags);

	if(renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		camera.w = app->win->screenSurface->w;
		camera.h = app->win->screenSurface->h;
		camera.x = 0;
		camera.y = 0;
	}
	layers.resize(MAX_LAYERS);

	return ret;
}

// Called before the first frame
bool Render::Start()
{
	LOG("render start");
	
	// back background
	SDL_RenderGetViewport(renderer, &viewport);

	return true;
}

// Called each loop iteration
bool Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

bool Render::Update(float dt)
{
	return true;
}

bool Render::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);

	//Sort

	Draw();


	SDL_RenderPresent(renderer);

	//Clear layers

	for (int i = 0; i < MAX_LAYERS; i++)
	{
		layers[i].clear();
	}

	return true;
}

// Called before quitting
bool Render::CleanUp()
{
	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

// L02: DONE 6: Implement a method to load the state, for now load camera's x and y
// Load Game State
bool Render::LoadState(pugi::xml_node& data)
{
	camera.x = data.child("camera").attribute("x").as_int();
	camera.y = data.child("camera").attribute("y").as_int();

	return true;
}

// L02: DONE 8: Create a method to save the state of the renderer
// Save Game State
bool Render::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node cam = data.append_child("camera");

	cam.append_attribute("x") = camera.x;
	cam.append_attribute("y") = camera.y;

	return true;
}

void Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

void Render::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

//// Blit to screen
//bool Render::DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, double angle, int pivotX, int pivotY) const
//{
//	bool ret = true;
//	uint scale = app->win->GetScale();
//
//	SDL_Rect rect;
//	rect.x = (int)(camera.x * speed) + x * scale;
//	rect.y = (int)(camera.y * speed) + y * scale;
//
//	if(section != NULL)
//	{
//		rect.w = section->w;
//		rect.h = section->h;
//	}
//	else
//	{
//		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
//	}
//
//	rect.w *= scale;
//	rect.h *= scale;
//
//	SDL_Point* p = NULL;
//	SDL_Point pivot;
//
//	if(pivotX != INT_MAX && pivotY != INT_MAX)
//	{
//		pivot.x = pivotX;
//		pivot.y = pivotY;
//		p = &pivot;
//	}
//
//	if(SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, SDL_FLIP_NONE) != 0)
//	{
//		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
//		ret = false;
//	}
//
//	return ret;
//}
//
//bool Render::DrawRectangle(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled, bool use_camera) const
//{
//	bool ret = true;
//	uint scale = app->win->GetScale();
//
//	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
//	SDL_SetRenderDrawColor(renderer, r, g, b, a);
//
//	SDL_Rect rec(rect);
//	if(use_camera)
//	{
//		rec.x = (int)(camera.x + rect.x * scale);
//		rec.y = (int)(camera.y + rect.y * scale);
//		rec.w *= scale;
//		rec.h *= scale;
//	}
//
//	int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);
//
//	if(result != 0)
//	{
//		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
//		ret = false;
//	}
//
//	return ret;
//}
//
//bool Render::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
//{
//	bool ret = true;
//	uint scale = app->win->GetScale();
//
//	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
//	SDL_SetRenderDrawColor(renderer, r, g, b, a);
//
//	int result = -1;
//
//	if(use_camera)
//		result = SDL_RenderDrawLine(renderer, camera.x + x1 * scale, camera.y + y1 * scale, camera.x + x2 * scale, camera.y + y2 * scale);
//	else
//		result = SDL_RenderDrawLine(renderer, x1 * scale, y1 * scale, x2 * scale, y2 * scale);
//
//	if(result != 0)
//	{
//		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
//		ret = false;
//	}
//
//	return ret;
//}
//
//bool Render::DrawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
//{
//	bool ret = true;
//	uint scale = app->win->GetScale();
//
//	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
//	SDL_SetRenderDrawColor(renderer, r, g, b, a);
//
//	int result = -1;
//	SDL_Point points[360];
//
//	float factor = (float)M_PI / 180.0f;
//
//	for(uint i = 0; i < 360; ++i)
//	{
//		points[i].x = (int)(x + radius * cos(i * factor));
//		points[i].y = (int)(y + radius * sin(i * factor));
//	}
//
//	result = SDL_RenderDrawPoints(renderer, points, 360);
//
//	if(result != 0)
//	{
//		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
//		ret = false;
//	}
//
//	return ret;
//}

void Render::AddrenderObject(SDL_Texture* texture, iPoint pos, SDL_Rect section, int layer, float ordeninlayer, double angle, bool isFlipH, bool tosort, float scale, float speed)
{
	renderObject renderobject;

	renderobject.texture = texture;
	renderobject.section = section;
	renderobject.Ordeninlayer = ordeninlayer;
	renderobject.speed = speed;
	renderobject.toSort = tosort;
	renderobject.angle = angle;
	renderobject.renderRect.x = (int)(app->render->camera.x * speed) + pos.x * scale;
	renderobject.renderRect.y = (int)(app->render->camera.y * speed) + pos.y * scale;

	if (layer == 3) renderobject.speed = 0;

	if (section.w != 0 || section.h != 0)
	{
		renderobject.renderRect.w = section.w;
		renderobject.renderRect.h = section.h;
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
		renderobject.flip = SDL_FLIP_NONE;
	}
	else
	{
		renderobject.flip = SDL_FLIP_HORIZONTAL;
	}

	layers[layer].push_back(renderobject);
}

void Render::Draw()
{
	for each (auto renderObj in layers[0])
	{
		if (IsinCamera(&renderObj))
		{
			if (renderObj.section.w == 0 || renderObj.section.h == 0)
			{
				if (SDL_RenderCopyEx(renderer, renderObj.texture, nullptr, &renderObj.renderRect, renderObj.angle, NULL, renderObj.flip) != 0)
				{
					printf_s("Error in Draw Function. SDL_RenderCopy error: %s", SDL_GetError());
				}
			}
			else
			{
				if (SDL_RenderCopyEx(renderer, renderObj.texture, &renderObj.section, &renderObj.renderRect, renderObj.angle, NULL, renderObj.flip) != 0)
				{
					printf_s("Error in Draw Function. SDL_RenderCopy error: %s", SDL_GetError());
				}
			}
		}
	}

	for each (auto renderObj in layers[1])
	{
		if (IsinCamera(&renderObj))
		{
			if (renderObj.section.w == 0 || renderObj.section.h == 0)
			{
				if (SDL_RenderCopyEx(renderer, renderObj.texture, nullptr, &renderObj.renderRect, renderObj.angle, NULL, renderObj.flip) != 0)
				{
					printf_s("Error in Draw Function. SDL_RenderCopy error: %s", SDL_GetError());
				}
			}
			else
			{
				if (SDL_RenderCopyEx(renderer, renderObj.texture, &renderObj.section, &renderObj.renderRect, renderObj.angle, NULL, renderObj.flip) != 0)
				{
					printf_s("Error in Draw Function. SDL_RenderCopy error: %s", SDL_GetError());
				}
			}
		}
	}

	for each (auto renderObj in layers[2])
	{
		if (IsinCamera(&renderObj))
		{
			if (renderObj.section.w == 0 || renderObj.section.h == 0)
			{
				if (SDL_RenderCopyEx(renderer, renderObj.texture, nullptr, &renderObj.renderRect, renderObj.angle, NULL, renderObj.flip) != 0)
				{
					printf_s("Error in Draw Function. SDL_RenderCopy error: %s", SDL_GetError());
				}
			}
			else
			{
				if (SDL_RenderCopyEx(renderer, renderObj.texture, &renderObj.section, &renderObj.renderRect, renderObj.angle, NULL, renderObj.flip) != 0)
				{
					printf_s("Error in Draw Function. SDL_RenderCopy error: %s", SDL_GetError());
				}
			}
		}
	}

}

bool Render::IsinCamera(const renderObject* renderObj)
{

	SDL_Rect camera = {(-app->render->camera.x + renderObj->renderRect.x),(-app->render->camera.y + renderObj->renderRect.y),app->render->camera.w,app->render->camera.h };
	SDL_Rect r = { renderObj->renderRect.x ,renderObj->renderRect.y,renderObj->renderRect.w ,renderObj->renderRect.h };

	return SDL_HasIntersection(&camera, &r);
}

void Render::SortingRenderObjectsWithOrdenInLayer(vector<renderObject>& vectorofobjectstosort)
{

	int small;
	int length = vectorofobjectstosort.size();

	for (int i = 0; i < length - 1; i++)
	{
		small = i;
		for (int j = i + 1; j < length; j++)
		{
			if (vectorofobjectstosort[j].Ordeninlayer < vectorofobjectstosort[small].Ordeninlayer)
			{
				small = j;
			}
		}
		swap(vectorofobjectstosort[i], vectorofobjectstosort[small]);

	}

}