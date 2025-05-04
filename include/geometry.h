#pragma once
#include <iostream>

/**
 * @class Point
 * @brief Represents a 2D point with integer coordinates.
 */
class Point
{
public:
    int x; ///< X coordinate
    int y; ///< Y coordinate
    /**
     * @brief Default constructor. Initializes point to (0, 0).
     */
    Point();
    /**
     * @brief Constructs a point with given coordinates.
     * @param x X coordinate
     * @param y Y coordinate
     */
    Point(int x, int y);
    /**
     * @brief Less-than operator for comparison.
     * @param other Point to compare
     * @return True if this point is less than other
     */
    bool operator<(const Point &other) const;
    /**
     * @brief Equality operator.
     * @param other Point to compare
     * @return True if points are equal
     */
    bool operator==(const Point &other) const;
    /**
     * @brief Output stream operator.
     * @param os Output stream
     * @param p Point to output
     * @return Reference to output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Point &p);
    /**
     * @brief Input stream operator.
     * @param is Input stream
     * @param p Point to input
     * @return Reference to input stream
     */
    friend std::istream &operator>>(std::istream &is, Point &p);
};

/**
 * @class Rectangle
 * @brief Represents a rectangle defined by top-left point, width, and height.
 */
class Rectangle
{
public:
    Point top_left; ///< Top-left corner
    int width;      ///< Width
    int height;     ///< Height
    /**
     * @brief Default constructor. Initializes rectangle at (0,0) with zero size.
     */
    Rectangle();
    /**
     * @brief Constructs a rectangle from coordinates and size.
     * @param x X coordinate of top-left
     * @param y Y coordinate of top-left
     * @param w Width
     * @param h Height
     */
    Rectangle(int x, int y, int w, int h);
    /**
     * @brief Constructs a rectangle from a point and size.
     * @param p Top-left point
     * @param w Width
     * @param h Height
     */
    Rectangle(const Point &p, int w, int h);
    /**
     * @brief Constructs a rectangle from two points.
     * @param top_left Top-left point
     * @param bottom_right Bottom-right point
     */
    Rectangle(const Point &top_left, const Point &bottom_right);
    /**
     * @brief Output stream operator.
     * @param os Output stream
     * @param p Rectangle to output
     * @return Reference to output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Rectangle &p);
    /**
     * @brief Input stream operator.
     * @param is Input stream
     * @param p Rectangle to input
     * @return Reference to input stream
     */
    friend std::istream &operator>>(std::istream &is, Rectangle &p);
    /**
     * @brief Returns the top-left and bottom-right corners as a pair.
     * @return Pair of points (top-left, bottom-right)
     */
    std::pair<Point, Point> getCorners() const;
    /**
     * @brief Equality operator.
     * @param other Rectangle to compare
     * @return True if rectangles are equal
     */
    bool operator==(const Rectangle &other) const;
    /**
     * @brief Adds a scalar to the rectangle's position.
     * @param scalar Value to add
     * @return Resulting rectangle
     */
    Rectangle operator+(const int scalar) const;
    /**
     * @brief Subtracts a scalar from the rectangle's position.
     * @param scalar Value to subtract
     * @return Resulting rectangle
     */
    Rectangle operator-(const int scalar) const;
    /**
     * @brief Returns the intersection of two rectangles.
     * @param other Rectangle to intersect with
     * @return Intersection rectangle
     */
    Rectangle operator&(const Rectangle &other) const;
    /**
     * @brief Returns the union of two rectangles.
     * @param other Rectangle to union with
     * @return Union rectangle
     */
    Rectangle operator|(const Rectangle &other) const;
};