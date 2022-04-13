#include "Player.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"

Player::Player()
{

    position = { 20,20 };
    player = { position.x,position.y,22,26 };

    //IDLE Anim
    idleAnim.PushBack({ 0,14,23,26 });
    idleAnim.PushBack({ 32,14,23,26 });
    idleAnim.PushBack({ 64,14,23,26 });//IDLE
    idleAnim.PushBack({ 96,14,23,26 });
    idleAnim.PushBack({ 128,14,23,26 });
    idleAnim.PushBack({ 160,14,23,26 });
    idleAnim.PushBack({ 192,14,23,26 });
    idleAnim.PushBack({ 224,14,23,26 });
    idleAnim.PushBack({ 256,14,23,26 });
    idleAnim.PushBack({ 288,14,23,26 });
    idleAnim.PushBack({ 320,14,23,26 });
    idleAnim.PushBack({ 0,14,23,26 });
    idleAnim.speed = 0.25;
    idleAnim.hasIdle = false;

    //Right Anim
    rightAnim.PushBack({ 0,45,25,28 });
    rightAnim.PushBack({ 32,45,25,28 });
    rightAnim.PushBack({ 64,45,25,28 });
    rightAnim.PushBack({ 96,45,25,28 });
    rightAnim.PushBack({ 127,45,25,28 });
    rightAnim.PushBack({ 159,45,25,28 });
    rightAnim.PushBack({ 192,45,25,28 });
    rightAnim.PushBack({ 224,45,25,28 });
    rightAnim.PushBack({ 256,45,25,28 });
    rightAnim.PushBack({ 288,45,25,28 });
    rightAnim.PushBack({ 319,45,25,28 });
    rightAnim.PushBack({ 351,45,25,28 });
    rightAnim.PushBack({ 0,45,25,28 });
    rightAnim.speed = 0.30;
    rightAnim.hasIdle = false;
    //Left Anim
    leftAnim.PushBack({ 0,45,25,28 });
    leftAnim.PushBack({ 32,45,25,28 });
    leftAnim.PushBack({ 64,45,25,28 });
    leftAnim.PushBack({ 96,45,25,28 });
    leftAnim.PushBack({ 127,45,25,28 });
    leftAnim.PushBack({ 159,45,25,28 });
    leftAnim.PushBack({ 192,45,25,28 });
    leftAnim.PushBack({ 224,45,25,28 });
    leftAnim.PushBack({ 256,45,25,28 });
    leftAnim.PushBack({ 288,45,25,28 });
    leftAnim.PushBack({ 319,45,25,28 });
    leftAnim.PushBack({ 351,45,25,28 });
    leftAnim.PushBack({ 0,45,25,28 });
    leftAnim.speed = 0.30;
    leftAnim.hasIdle = false;

    currentAnim = &idleAnim;

}

Player::~Player()
{
}

bool Player::Start()
{
    
    tex = app->tex->Load("Assets/textures/Ninja_Frog_Sprites.png");

    return true;
}

bool Player::PreUpdate()
{
    isflip = false;
    return true;
}

bool Player::Update()
{

    if(app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
    {
        position.y += speed;
    }
    if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
    {
        position.y -= speed;
    }
    if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
    {
        position.x += speed;
        currentAnim = &rightAnim;
    }
    if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
    {
        position.x -= speed;
        currentAnim = &leftAnim;
        isflip = true;
    }

    currentAnim->Update();

    return true;
}

bool Player::PostUpdate()
{

    animsections = &currentAnim->GetCurrentFrame();
    //Aqui proba
    if (isflip == false)
    {
        app->render->AddrenderObject(tex, { position.x,position.y }, *(animsections), 2, 1.0f, 0.0f);
    }
    else
    {
        app->render->AddrenderObject(tex, { position.x,position.y }, *(animsections), 2, 1.0f, 0.0f,true);
    }
    return true;
}

bool Player::CleanUp() {

    SDL_DestroyTexture(tex);
    tex = nullptr;
    currentAnim = nullptr;

    return true;
}