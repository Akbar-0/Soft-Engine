#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D
{
    public:
        float X, Y;

    public:
        Vector2D(float x = 0, float y = 0): X(x), Y(y) {}

    public:
        //addition +
        inline Vector2D operator+(const Vector2D& v2) const {
            return Vector2D(X + v2.X, Y + v2.Y);
        }

        //difference -
        inline Vector2D operator-(const Vector2D& v2) const {
            return Vector2D(X - v2.X, Y - v2.Y);
        }

        //scalar prdct *
        inline Vector2D operator*(const float scalar) const {
            return Vector2D(X*scalar, Y*scalar);
        }

        void Log(std::string msg = ""){
            std::cout << msg << "(X Y) = (" << X << " " << Y << ")"<< std::endl;
        }

};

#endif // VECTOR2D_H
