#include"Vector2.h"

Vector2::Vector2(int X, int Y) : 
x(X), y(Y) {}

Vector2::Vector2(const Vector2& other) : 
x(other.x), y(other.y) {}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(this->x - other.x, this->y - other.y);
}
