#ifndef WARRIOR_H
#define WARRIOR_H

#include "Collider.h"
#include "Vector2D.h"
#include "Character.h"
#include "SeqAnimation.h"
#include "SpriteAnimation.h"
#include "RigidBody.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 10.0f

#define RUN_FORCE 5.0f
#define ATTACK_TIME 20.0f

class Warrior: public Character
{
    public:
        Warrior(Properties* props);

        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);

    private:
        void AnimationState();

    private:
        bool m_IsRunning;
        bool m_IsJumping;
        bool m_IsFalling;
        bool m_IsGrounded;
        bool m_IsAttacking;
        bool m_IsCrouching;
        bool m_IsFacingLeft;

        float m_JumpTime;
        float m_JumpForce;
        float m_AttackTime;

        Collider* m_Collider;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
        SpriteAnimation* m_Animation;
};

#endif // WARRIOR_H
