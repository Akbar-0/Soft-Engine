#ifndef PARTICLE_H
#define PARTICLE_H

#include "Transform.h"
#include "Camera.h"
#include <string>
#include "Engine.h"
#include "TextureManager.h"

class Particle
{
    public:
        Particle(Transform tf, float vX, float vY, Uint32 lifetime) {
            m_vX = vX; m_vY = vY;
            m_Tf.X = tf.X, m_Tf.Y = tf.Y;
            m_LifeTime = (SDL_GetTicks() + lifetime);
        }

    private:
        Transform m_Tf;
        Uint32 m_LifeTime;
        float m_vX, m_vY;
};

#endif // PARTICLE_H
