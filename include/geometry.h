#pragma once
#include <iostream>

class Point
{
public:
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    bool operator<(const Point &other) const;
    friend std::ostream &operator<<(std::ostream &os, const Point &p);
    friend std::istream &operator>>(std::istream &is, Point &p);
};

class Rectangle
{
public:
    Point top_left;
    int width;
    int height;
    Rectangle() : top_left(0, 0), width(0), height(0) {}
    Rectangle(int x, int y, int w, int h) : top_left(x, y), width(w), height(h) {}
    Rectangle(const Point &p, int w, int h) : top_left(p), width(w), height(h) {}
    Rectangle(const Point &top_left, const Point &bottom_right) : top_left(top_left), width(bottom_right.x - top_left.x), height(bottom_right.y - top_left.y) {}
    friend std::ostream &operator<<(std::ostream &os, const Rectangle &p);
    friend std::istream &operator>>(std::istream &is, Rectangle &p);
    std::pair<Point, Point> getCorners() const;
    Rectangle operator+(const int scalar) const;
    Rectangle operator-(const int scalar) const;
    Rectangle operator&(const Rectangle &other) const;
    Rectangle operator|(const Rectangle &other) const;
};