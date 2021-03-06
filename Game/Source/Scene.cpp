#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"



#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// L03: DONE: Load map
	//app->map->Load("maptest.tmx");

	backgroundmap = app->tex->Load("Assets/textures/maptest.png");

	column = app->tex->Load("Assets/textures/column.png");

	froggy = new Player();

	froggy->Start();
	
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	/*btn1 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Test1", { (app->win->GetWidth() / 2) - 300, app->win->GetWidth() / 10, 160, 40 }, this);
	btn2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Test2", { (app->win->GetWidth() / 2) + 300, app->win->GetWidth() / 10, 160, 40 }, this);*/

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	froggy->PreUpdate();
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	// L08: TODO 6: Make the camera movement independent of framerate
	float speed = 1.5f; 
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		app->render->camera.y -= speed;
	}
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		app->render->camera.y += speed;
	}
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		app->render->camera.x -= speed;
	}
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		app->render->camera.x += speed;
	}
	froggy->Update();
	// Draw map
	//app->map->Draw();

	//Draw GUI
	/*app->guiManager->Draw();*/

	

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	froggy->PostUpdate();

	for (int i = 1; i < 30; i++)
	{
		for (int j = 1; j < 30; j++)
		{
			app->render->AddrenderObject(column, { 100 * j,100 * i }, { 0,0,0,0 }, 2, 0.5f, 0.0f);
		}
	}

	/*app->render->DrawTexture(backgroundmap, 0, 0);*/
	app->render->AddrenderObject(backgroundmap, { 0,0 }, { 0,0,0,0 }, 1, 1.0f,0.0f);

	return ret;
}


//bool Scene::OnGuiMouseClickEvent(GuiControl* control)
//{
//
//	switch (control->type)
//	{
//	case GuiControlType::BUTTON:
//	{
//		//Checks the GUI element ID
//		if (control->id == 1) 
//		{
//			LOG("Click on button 1");
//		}
//
//		if (control->id == 2)
//		{
//			LOG("Click on button 2");
//		}
//		
//	}
//	//Other cases here
//
//	default: break;
//	}
//
//	return true;
//}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	froggy->CleanUp();



	return true;
}
