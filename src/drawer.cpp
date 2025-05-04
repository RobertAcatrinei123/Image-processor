#include "drawer.h"

int Drawer::distance(int x1, int y1, int x2, int y2)
{
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void Drawer::drawCircle(Image &img, const Point &center, int radius, unsigned char color)
{
    for (int y = 0; y < img.height(); ++y)
    {
        for (int x = 0; x < img.width(); ++x)
        {
            if (distance(center.x, center.y, x, y) == radius)
            {
                img.at(x, y) = color;
            }
        }
    }
}

void Drawer::drawLine(Image &img, const Point &p1, const Point &p2, unsigned char color)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    float norm = std::sqrt(dx * dx + dy * dy);
    dx /= norm;
    dy /= norm;

    float x = p1.x;
    float y = p1.y;

    //std::cerr << "Drawing line from (" << p1.x << ", " << p1.y << ") to (" << p2.x << ", " << p2.y << ") with delta" << " (" << dx << ", " << dy << ")" << std::endl;

    while (x < img.width() && y < img.height() && x >= 0 && y >= 0 && !(int(x) == p2.x && int(y) == p2.y))
    {
        img.at(int(x), int(y)) = color;
        x += dx;
        y += dy;
    }
}

void Drawer::drawRectangle(Image &img, const Rectangle &rect, unsigned char color)
{
    drawLine(img, rect.top_left, Point(rect.top_left.x + rect.width, rect.top_left.y), color);
    drawLine(img, rect.top_left, Point(rect.top_left.x, rect.top_left.y + rect.height), color);
    drawLine(img, Point(rect.top_left.x + rect.width, rect.top_left.y), Point(rect.top_left.x + rect.width, rect.top_left.y + rect.height), color);
    drawLine(img, Point(rect.top_left.x, rect.top_left.y + rect.height), Point(rect.top_left.x + rect.width, rect.top_left.y + rect.height), color);
}

void Drawer::drawRectangle(Image &img, const Point &top_left, const Point &bottom_right, unsigned char color)
{
    drawRectangle(img, Rectangle(top_left, bottom_right), color);
}