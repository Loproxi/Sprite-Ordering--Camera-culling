#include "Player.h"
#include "App.h"
#include "Input.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Start()
{
    position = { 20,20 };
    player = new SDL_Rect{ position.x,position.y,15,25 };

    return true;
}

bool Player::PreUpdate()
{
    return true;
}

bool Player::Update()
{

    if(app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
    {
        position.y += speed;
    }
    if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
    {
        position.y -= speed;
    }
    if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
    {
        position.x += speed;
    }
    if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
    {
        position.x -= speed;
    }

    return true;
}

bool Player::PostUpdate()
{
    //Aqui proba
    app->render->AddrenderObject();
    return true;
}
