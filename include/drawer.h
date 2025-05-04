#include "image.h"
#include "geometry.h"

/**
 * @class Drawer
 * @brief Provides static methods for drawing shapes on images.
 */
class Drawer
{
private:
    /**
     * @brief Computes the Euclidean distance between two points.
     * @param x1 X coordinate of first point
     * @param y1 Y coordinate of first point
     * @param x2 X coordinate of second point
     * @param y2 Y coordinate of second point
     * @return Distance between the points
     */
    static int distance(int x1, int y1, int x2, int y2);

public:
    /**
     * @brief Draws a circle on an image.
     * @param img Image to draw on
     * @param center Center of the circle
     * @param radius Radius of the circle
     * @param color Color of the circle
     */
    static void drawCircle(Image &img, const Point &center, int radius, unsigned char color);
    /**
     * @brief Draws a line on an image.
     * @param img Image to draw on
     * @param p1 Starting point
     * @param p2 Ending point
     * @param color Color of the line
     */
    static void drawLine(Image &img, const Point &p1, const Point &p2, unsigned char color);
    /**
     * @brief Draws a rectangle on an image.
     * @param img Image to draw on
     * @param rect Rectangle to draw
     * @param color Color of the rectangle
     */
    static void drawRectangle(Image &img, const Rectangle &rect, unsigned char color);
    /**
     * @brief Draws a rectangle on an image using two points.
     * @param img Image to draw on
     * @param top_left Top-left point
     * @param bottom_right Bottom-right point
     * @param color Color of the rectangle
     */
    static void drawRectangle(Image &img, const Point &top_left, const Point &bottom_right, unsigned char color);
};