#pragma once
#include <string>
#include "geometry.h"

/**
 * @class Size
 * @brief Represents the size (width and height) of an object.
 */
class Size
{
private:
    int w; ///< Width
    int h; ///< Height

public:
    /**
     * @brief Default constructor. Initializes width and height to 0.
     */
    Size();
    /**
     * @brief Constructs a Size with given width and height.
     * @param w Width
     * @param h Height
     */
    Size(int w, int h);
    /**
     * @brief Returns the width.
     * @return Width
     */
    int width() const;
    /**
     * @brief Returns the height.
     * @return Height
     */
    int height() const;
    /**
     * @brief Checks equality with another Size.
     * @param other The other Size
     * @return True if equal, false otherwise
     */
    bool operator==(const Size &other) const;
    /**
     * @brief Checks inequality with another Size.
     * @param other The other Size
     * @return True if not equal, false otherwise
     */
    bool operator!=(const Size &other) const;
};

/**
 * @class Image
 * @brief Represents a grayscale image and provides image manipulation methods.
 */
class Image
{
private:
    Size s;                  ///< Image size
    unsigned char max_value; ///< Maximum pixel value
    unsigned char **data;    ///< 2D array of pixel data

public:
    /**
     * @brief Default constructor. Creates an empty image.
     */
    Image();
    /**
     * @brief Constructs an image with given width and height.
     * @param w Width
     * @param h Height
     */
    Image(int w, int h);
    /**
     * @brief Copy constructor.
     * @param other Image to copy
     */
    Image(const Image &other);
    /**
     * @brief Destructor. Releases memory.
     */
    ~Image();
    /**
     * @brief Assignment operator.
     * @param other Image to assign from
     * @return Reference to this image
     */
    Image &operator=(const Image &other);
    /**
     * @brief Returns the width of the image.
     * @return Width
     */
    int width() const;
    /**
     * @brief Returns the height of the image.
     * @return Height
     */
    int height() const;
    /**
     * @brief Returns the size of the image.
     * @return Size object
     */
    Size size() const;
    /**
     * @brief Saves the image to a file.
     * @param filename Output file name
     * @return True if successful, false otherwise
     */
    bool save(const std::string &filename) const;
    /**
     * @brief Loads the image from a file.
     * @param filename Input file name
     * @return True if successful, false otherwise
     */
    bool load(const std::string &filename);
    /**
     * @brief Writes the image to an output stream.
     * @param os Output stream
     * @param img Image to write
     * @return Reference to output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Image &img);
    /**
     * @brief Reads the image from an input stream.
     * @param is Input stream
     * @param img Image to read into
     * @return Reference to input stream
     */
    friend std::istream &operator>>(std::istream &is, Image &img);
    /**
     * @brief Adds two images.
     * @param other Image to add
     * @return Resulting image
     */
    Image operator+(const Image &other) const;
    /**
     * @brief Subtracts another image from this image.
     * @param other Image to subtract
     * @return Resulting image
     */
    Image operator-(const Image &other) const;
    /**
     * @brief Adds another image to this image in-place.
     * @param other Image to add
     * @return Reference to this image
     */
    Image operator+=(const Image &other);
    /**
     * @brief Subtracts another image from this image in-place.
     * @param other Image to subtract
     * @return Reference to this image
     */
    Image operator-=(const Image &other);
    /**
     * @brief Multiplies the image by a scalar.
     * @param scalar Scalar value
     * @return Resulting image
     */
    Image operator*(const int scalar) const;
    /**
     * @brief Adds a scalar to the image.
     * @param scalar Scalar value
     * @return Resulting image
     */
    Image operator+(const int scalar) const;
    /**
     * @brief Subtracts a scalar from the image.
     * @param scalar Scalar value
     * @return Resulting image
     */
    Image operator-(const int scalar) const;
    /**
     * @brief Adds a scalar to the image in-place.
     * @param scalar Scalar value
     * @return Reference to this image
     */
    Image operator+=(const int scalar);
    /**
     * @brief Subtracts a scalar from the image in-place.
     * @param scalar Scalar value
     * @return Reference to this image
     */
    Image operator-=(const int scalar);
    /**
     * @brief Multiplies the image by a scalar in-place.
     * @param scalar Scalar value
     * @return Reference to this image
     */
    Image operator*=(const int scalar) const;
    /**
     * @brief Checks if two images are equal.
     * @param other Image to compare
     * @return True if equal, false otherwise
     */
    bool operator==(const Image &other) const;
    /**
     * @brief Checks if two images are not equal.
     * @param other Image to compare
     * @return True if not equal, false otherwise
     */
    bool operator!=(const Image &other) const;
    /**
     * @brief Checks if the image is empty.
     * @return True if empty, false otherwise
     */
    bool empty() const;
    /**
     * @brief Returns a reference to the pixel at (x, y).
     * @param x X coordinate
     * @param y Y coordinate
     * @return Reference to pixel value
     */
    unsigned char &at(int x, int y);
    /**
     * @brief Returns a reference to the pixel at a given point.
     * @param p Point
     * @return Reference to pixel value
     */
    unsigned char &at(const Point &p);
    /**
     * @brief Gets the pixel value at (x, y), with optional padding.
     * @param x X coordinate
     * @param y Y coordinate
     * @param pad If true, pads out-of-bounds with 0
     * @return Pixel value
     */
    unsigned char getAt(int x, int y, bool pad = false) const;
    /**
     * @brief Gets the pixel value at a given point, with optional padding.
     * @param p Point
     * @param pad If true, pads out-of-bounds with 0
     * @return Pixel value
     */
    unsigned char getAt(const Point &p, bool pad = false) const;
    /**
     * @brief Returns a pointer to the row at y.
     * @param y Row index
     * @return Pointer to row
     */
    unsigned char *row(int y);
    /**
     * @brief Releases the image data.
     */
    void release();
    /**
     * @brief Returns a region of interest (ROI) as a new image.
     * @param r Rectangle defining the ROI
     * @return ROI image
     */
    Image ROI(const Rectangle &r) const;
    /**
     * @brief Returns a region of interest (ROI) as a new image.
     * @param x X coordinate
     * @param y Y coordinate
     * @param w Width
     * @param h Height
     * @return ROI image
     */
    Image ROI(int x, int y, int w, int h) const;
    /**
     * @brief Creates a zero-filled image.
     * @param w Width
     * @param h Height
     * @return Zero-filled image
     */
    static Image zeros(int w, int h);
    /**
     * @brief Creates a one-filled image.
     * @param w Width
     * @param h Height
     * @return One-filled image
     */
    static Image ones(int w, int h);
};