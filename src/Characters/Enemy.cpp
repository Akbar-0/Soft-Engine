#include "Enemy.h"

#include "Camera.h"
#include <iostream>
#include "ObjectFactory.h"
#include "CollisionHandler.h"

static Registrar<Enemy> registrar("MANW");

Enemy::Enemy(Properties* props): Character(props)
{
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.5f);
    m_Collider = new Collider();
    m_Collider->SetBuffer(-55, -35, 50, -30);

    m_Animation = new SeqAnimation(false);
    m_Animation->Parse("assets/animations.aml");
    m_Animation->SetCurrentSeq("manWA");
}

void Enemy::Draw()
{
    m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 2, 2, 1, m_Flip);

    //m_Collider->DrawRect();
}

void Enemy::Clean()
{

}

void Enemy::Update(float dt)
{
    // Move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 46, 70);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->X = m_LastSafePosition.X;

    // Move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 46, 70);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->Y = m_LastSafePosition.Y;

    m_Animation->Update(dt);

    if(m_Animation->IsEnded()){
        m_Animation->SetRepeat(true);
        m_Animation->SetCurrentSeq("manWB");
    }
}
