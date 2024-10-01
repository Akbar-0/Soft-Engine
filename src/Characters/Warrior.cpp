#include "Warrior.h"

#include "SDL.h"
#include "Input.h"
#include "Camera.h"
#include "Engine.h"
#include "ObjectFactory.h"
#include "TextureManager.h"
#include "CollisionHandler.h"

#define BASIC_ANIM_DELAY 80  //Increase this to lower the speed

static Registrar<Warrior> registrar("PLAYER");

Warrior::Warrior(Properties* props): Character(props){
    m_IsRunning = false;
    m_IsJumping = false;
    m_IsFalling = false;
    m_IsGrounded = false;
    m_IsAttacking = false;
    m_IsCrouching = false;
    m_IsFacingLeft = false;

    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-45, -10, 70, -10);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.5f);

    m_Animation = new SpriteAnimation();
    m_Animation->SetProps(m_TextureID, 1, 10, BASIC_ANIM_DELAY);
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, 1, 1, m_Flip);

    //m_Collider->DrawRect();
}

void Warrior::Update(float dt)
{
    m_IsRunning = false;
    m_IsCrouching = false;
    m_RigidBody->UnSetForce();

    // Run Forward
    if((Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) && !m_IsAttacking && !m_IsCrouching){
        m_RigidBody->ApplyForceX(FORWARD*RUN_FORCE);
        //m_Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
        m_IsFacingLeft = false;
        m_Collider->SetBuffer(-45, -10, 70, -10);
    }

    // Run Backward
    if((Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFT) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) && !m_IsAttacking && !m_IsCrouching){
        m_RigidBody->ApplyForceX(BACKWARD*RUN_FORCE);
        //m_Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
        m_IsFacingLeft = true;
        m_Collider->SetBuffer(-60, -10, 70, -10);
    }

    // Crouch
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_C)){
        m_RigidBody->UnSetForce();
        m_IsCrouching = true;
    }

    // Attack
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K)){
        m_RigidBody->UnSetForce();
        m_IsAttacking = true;
    }

    // Jump
    if((Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)) && m_IsGrounded){
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }

     // Keep Jumping
    if((Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)) && m_IsJumping && m_JumpTime > 0){
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    else{
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    // Fall
    if(m_RigidBody->Velocity().Y > 0 && !m_IsGrounded){
        m_IsFalling = true;
    }
    else{
        m_IsFalling = false;
    }

    // Attack Timer
    if(m_IsAttacking && m_AttackTime > 0){
        m_AttackTime -= dt;
    }
    else{
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }

    // Move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->X = m_LastSafePosition.X;

    // Move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())){
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else{
        m_IsGrounded = false;
    }


    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;

    AnimationState();
    m_Animation->Update(dt);
}

void Warrior::AnimationState()
{
    if(!m_IsRunning && !m_IsCrouching && !m_IsJumping && !m_IsFalling && !m_IsAttacking){
        m_Flip = SDL_FLIP_NONE;
            if(m_IsFacingLeft)
              m_Flip = SDL_FLIP_HORIZONTAL;
        m_Animation->SetProps("player_idle", 1, 7, BASIC_ANIM_DELAY/*, SDL_FLIP_NONE*/);
    }
    if(m_IsRunning && !m_IsCrouching){
             if(m_IsFacingLeft)
               m_Flip = SDL_FLIP_NONE;
             else
               m_Flip = SDL_FLIP_HORIZONTAL;
        m_Animation->SetProps("player_run", 1, 10, BASIC_ANIM_DELAY/*, SDL_FLIP_HORIZONTAL*/);
    }
    else if(m_IsCrouching){
             if(m_IsFacingLeft)
               m_Flip = SDL_FLIP_HORIZONTAL;
             else
               m_Flip = SDL_FLIP_NONE;
             m_Animation->SetProps("player_crouch", 1, 2, BASIC_ANIM_DELAY+120/*, SDL_FLIP_NONE*/);
    }
    else if(m_IsJumping){
             if(m_IsFacingLeft)
               m_Flip = SDL_FLIP_HORIZONTAL;
             else
               m_Flip = SDL_FLIP_NONE;
             m_Animation->SetProps("player_jump", 1, 2, BASIC_ANIM_DELAY+180/*, SDL_FLIP_NONE*/);
    }
    else if(m_IsFalling){
             if(m_IsFacingLeft)
               m_Flip = SDL_FLIP_HORIZONTAL;
             else
               m_Flip = SDL_FLIP_NONE;
             m_Animation->SetProps("player_fall", 1, 2, BASIC_ANIM_DELAY+270/*, SDL_FLIP_NONE*/);
    }
    else if(m_IsAttacking){
             if(m_IsFacingLeft)
               m_Flip = SDL_FLIP_NONE;
             else
               m_Flip = SDL_FLIP_HORIZONTAL;
             m_Animation->SetProps("player_attack", 1, 5, BASIC_ANIM_DELAY/*, SDL_FLIP_HORIZONTAL*/);
    }
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}
