#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include"Vector2D.h"

#define UNIT_MASS 1.0f
#define GRAVITY 9.80665f

#define FORWARD 1
#define BACKWARD -1

#define UPWARD -1
#define DOWNWARD 1

class RigidBody
{
    public:
        RigidBody() {
            m_Mass = UNIT_MASS;
            m_Gravity = GRAVITY;
        }

        // Setters for mass and gravity
        inline void SetMass(float mass) {m_Mass = mass;}
        inline void SetGravity(float gravity) {m_Gravity = gravity;}

        // Force
        inline void ApplyForce(Vector2D F) {m_Force = F;}
        inline void ApplyForceX(float Fx) {m_Force.X = Fx;}
        inline void ApplyForceY(float Fy) {m_Force.Y = Fy;}
        inline void UnSetForce() {m_Force = Vector2D(0,0);}

        // Setters for mass, position, velocity, acceleration
        inline float GetMass() {return m_Mass;}
        inline Vector2D Position() {return m_Position;}
        inline Vector2D Velocity() {return m_Velocity;}
        inline Vector2D Acceleration() {return m_Acceleration;}

        // Friction
        inline void ApplyFriction(Vector2D Fr) {m_Friction = Fr;}
        inline void UnSetFriction() {m_Friction = Vector2D(0,0);}

        // Update Method
        void Update(float dt){
            m_Acceleration.X = (m_Force.X + m_Friction.X)/m_Mass;
            m_Acceleration.Y = m_Gravity + m_Force.Y/m_Mass;
            m_Velocity = m_Acceleration*dt;
            m_Position = m_Velocity*dt;
        }

    private:
        float m_Mass;
        float m_Gravity;

        Vector2D m_Force;
        Vector2D m_Friction;

        Vector2D m_Position;
        Vector2D m_Velocity;
        Vector2D m_Acceleration;

};

#endif // RIGIDBODY_H
