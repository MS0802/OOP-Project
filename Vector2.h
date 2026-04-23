struct Vector2 {
    int x;
    int y;
    Vector2(int X, int Y);
    Vector2(const Vector2& other);
    
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
};
