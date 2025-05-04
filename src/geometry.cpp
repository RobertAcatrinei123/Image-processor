#include "geometry.h"

std::ostream &operator<<(std::ostream &os, const Point &p)
{
    os << p.x << " " << p.y;
    return os;
}

std::istream &operator>>(std::istream &is, Point &p)
{
    is >> p.x >> p.y;
    return is;
}

std::ostream &operator<<(std::ostream &os, const Rectangle &r)
{
    os << r.top_left << " " << r.width << " " << r.height;
    return os;
}

std::istream &operator>>(std::istream &is, Rectangle &r)
{
    is >> r.top_left >> r.width >> r.height;
    return is;
}

bool Point::operator<(const Point &other) const
{
    return (x < other.x) || (x == other.x && y < other.y);
}

std::pair<Point, Point> Rectangle::getCorners() const
{
    return {top_left, Point(top_left.x + width, top_left.y + height)};
}

Rectangle Rectangle::operator+(const int scalar) const
{
    return Rectangle(top_left.x + scalar, top_left.y + scalar, width, height);
}

Rectangle Rectangle::operator-(const int scalar) const
{
    return Rectangle(top_left.x - scalar, top_left.y - scalar, width, height);
}

Rectangle Rectangle::operator&(const Rectangle &other) const
{
    auto r1 = getCorners();
    auto r2 = other.getCorners();
    if (r2.first < r1.first)
    {
        std::swap(r1, r2);
    }
    if (r1.second < r2.first)
    {
        return Rectangle();
    }
    return Rectangle(r2.first, r1.second);
}

Rectangle Rectangle::operator|(const Rectangle &other) const
{
    auto r1 = getCorners();
    auto r2 = other.getCorners();
    if (r2.first < r1.first)
    {
        std::swap(r1, r2);
    }
    return Rectangle(r1.first, r2.second);
}

bool Rectangle::operator==(const Rectangle &other) const
{
    return top_left == other.top_left && width == other.width && height == other.height;
}

bool Point::operator==(const Point &other) const
{
    return x == other.x && y == other.y;
}
