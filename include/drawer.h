#include "image.h"
#include "geometry.h"

class Drawer
{
private:
    static int distance(int x1, int y1, int x2, int y2);

public:
    static void drawCircle(Image &img, const Point &center, int radius, unsigned char color);
    static void drawLine(Image &img, const Point &p1, const Point &p2, unsigned char color);
    static void drawRectangle(Image &img, const Rectangle &rect, unsigned char color);
    static void drawRectangle(Image &img, const Point &top_left, const Point &bottom_right, unsigned char color);
};