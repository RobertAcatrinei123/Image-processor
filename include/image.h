#pragma once
#include <string>
#include "geometry.h"

class Size
{
private:
    int w;
    int h;

public:
    Size();
    Size(int w, int h);
    int width() const;
    int height() const;
};

class Image
{
private:
    Size s;
    unsigned char max_value;
    unsigned char **data;

public:
    Image();
    Image(int w, int h);
    Image(const Image &other);
    ~Image();
    Image &operator=(const Image &other);
    int width() const;
    int height() const;
    Size size() const;
    bool save(const std::string &filename) const;
    bool load(const std::string &filename);
    friend std::ostream &operator<<(std::ostream &os, const Image &img);
    friend std::istream &operator>>(std::istream &is, Image &img);
    Image operator+(const Image &other) const;
    Image operator-(const Image &other) const;
    Image operator+=(const Image &other);
    Image operator-=(const Image &other);
    Image operator*(const int scalar) const;
    Image operator+(const int scalar) const;
    Image operator-(const int scalar) const;
    Image operator+=(const int scalar);
    Image operator-=(const int scalar);
    Image operator*=(const int scalar) const;
    bool empty() const;
    unsigned char &at(int x, int y);
    unsigned char &at(const Point &p);
    unsigned char *row(int y);
    void release();
    Image ROI(const Rectangle &r) const;
    Image ROI(int x, int y, int w, int h) const;
    static Image zeros(int w, int h);
    static Image ones(int w, int h);
};