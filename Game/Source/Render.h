#ifndef __RENDER_H__
#define __RENDER_H__

#include "Module.h"

#include "Point.h"

#include "SDL/include/SDL.h"

#include <vector>

using namespace std;

struct renderObject
{
	SDL_Texture* texture;

	SDL_Rect* section;

	SDL_Rect renderRect;

	SDL_RendererFlip flip;

	int layer = 0;

	float Ordeninlayer = 1.0f;

	float speed = 1.0f;

	bool toSort = false;

};

class Render : public Module
{
public:

	Render();

	// Destructor
	virtual ~Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();



	// Drawing
	/*bool DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float speed = 1.0f, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX) const;
	bool DrawRectangle(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool useCamera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;*/

	// Set background color
	void SetBackgroundColor(SDL_Color color);

	//Research Project
	void SortingRenderObjectsWithOrdenInLayer(vector<renderObject>& vectorofobjectstosort);

	bool IsinCamera(const renderObject* renderObj);

	void AddrenderObject(SDL_Texture* texture, iPoint pos, SDL_Rect* section, int layer, float ordeninlayer, bool isFlipH = false, bool tosort = false, float scale = 1.0f, float speed = 1.0f);

	//Draw Function
public:

	SDL_Renderer* renderer;
	SDL_Rect camera = { 0, 0, 520, 520 };;
	SDL_Rect viewport;
	SDL_Color background;

private:

	vector< vector<renderObject>> layers;

};

#endif // __RENDER_H__