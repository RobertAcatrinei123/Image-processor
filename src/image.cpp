#include "image.h"
#include <math.h>

Size::Size() : w(0), h(0) {}
Size::Size(int w, int h) : w(w), h(h) {}
int Size::width() const { return w; }
int Size::height() const { return h; }
Image::Image() : s(0, 0), data(nullptr) {}

Image::Image(int w, int h) : s(w, h)
{
    data = new unsigned char *[h];
    for (int i = 0; i < h; ++i)
    {
        data[i] = new unsigned char[w];
    }
}

Image::Image(const Image &img) : s(img.s)
{
    data = new unsigned char *[s.height()];
    for (int i = 0; i < s.height(); ++i)
    {
        data[i] = new unsigned char[s.width()];
        for (int j = 0; j < s.width(); ++j)
        {
            data[i][j] = img.data[i][j];
        }
    }
}

Image::~Image()
{
    release();
}

Image &Image::operator=(const Image &img)
{
    if (this != &img)
    {
        release();
        s = img.s;
        data = new unsigned char *[s.height()];
        for (int i = 0; i < s.height(); ++i)
        {
            data[i] = new unsigned char[s.width()];
            for (int j = 0; j < s.width(); ++j)
            {
                data[i][j] = img.data[i][j];
            }
        }
    }
    return *this;
}

int Image::width() const { return s.width(); }
int Image::height() const { return s.height(); }
Size Image::size() const { return s; }

bool Image::save(const std::string &filename) const
{
    // Implement saving logic here
    return true;
}

bool Image::load(const std::string &filename)
{
    // Implement loading logic here
    return true;
}

std::ostream &operator<<(std::ostream &os, const Image &img)
{
    // Implement output logic here
    return os;
}

std::istream &operator>>(std::istream &is, Image &img)
{
    // Implement input logic here
    return is;
}

Image Image::operator+(const Image &other) const
{
    if (s.width() != other.s.width() || s.height() != other.s.height())
    {
        throw std::invalid_argument("Images must have the same size for addition.");
    }
    Image result(s.width(), s.height());
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {

            result.data[i][j] = std::clamp(data[i][j] + other.data[i][j], 0, 255);
        }
    }
    return result;
}

Image Image::operator-(const Image &other) const
{
    if (s.width() != other.s.width() || s.height() != other.s.height())
    {
        throw std::invalid_argument("Images must have the same size for subtraction.");
    }
    Image result(s.width(), s.height());
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            result.data[i][j] = std::clamp(data[i][j] - other.data[i][j], 0, 255);
        }
    }
    return result;
}

Image Image::operator+=(const Image &other)
{
    if (s.width() != other.s.width() || s.height() != other.s.height())
    {
        throw std::invalid_argument("Images must have the same size for addition.");
    }
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            data[i][j] += other.data[i][j];
            data[i][j] = std::clamp(int(data[i][j]), 0, 255);
        }
    }
    return *this;
}

Image Image::operator-=(const Image &other)
{
    if (s.width() != other.s.width() || s.height() != other.s.height())
    {
        throw std::invalid_argument("Images must have the same size for subtraction.");
    }
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            data[i][j] -= other.data[i][j];
            data[i][j] = std::clamp(int(data[i][j]), 0, 255);
        }
    }
    return *this;
}

Image Image::operator*(const int scalar) const
{
    Image result(s.width(), s.height());
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            result.data[i][j] = std::clamp(data[i][j] * scalar, 0, 255);
        }
    }
    return result;
}

Image Image::operator+(const int scalar) const
{
    Image result(s.width(), s.height());
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            result.data[i][j] = std::clamp(data[i][j] + scalar, 0, 255);
        }
    }
    return result;
}

Image Image::operator-(const int scalar) const
{
    Image result(s.width(), s.height());
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            result.data[i][j] = std::clamp(data[i][j] - scalar, 0, 255);
        }
    }
    return result;
}

Image Image::operator+=(const int scalar)
{
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            data[i][j] += scalar;
            data[i][j] = std::clamp(int(data[i][j]), 0, 255);
        }
    }
    return *this;
}

Image Image::operator-=(const int scalar)
{
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            data[i][j] -= scalar;
            data[i][j] = std::clamp(int(data[i][j]), 0, 255);
        }
    }
    return *this;
}

Image Image::operator*=(const int scalar) const
{
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            data[i][j] *= scalar;
            data[i][j] = std::clamp(int(data[i][j]), 0, 255);
        }
    }
    return *this;
}

bool Image::empty() const
{
    return s.width() == 0 || s.height() == 0;
}

unsigned char &Image::at(int x, int y)
{
    if (x < 0 || x >= s.width() || y < 0 || y >= s.height())
    {
        throw std::out_of_range("Index out of range");
    }
    return data[y][x];
}

unsigned char &Image::at(const Point &p)
{
    return at(p.x, p.y);
}

unsigned char *Image::row(int y)
{
    if (y < 0 || y >= s.height())
    {
        throw std::out_of_range("Row index out of range");
    }
    return data[y];
}

void Image::release()
{
    if (data)
    {
        for (int i = 0; i < s.height(); ++i)
        {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}
Image Image::ROI(int x, int y, int w, int h) const
{
    if (x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > s.width() || y + h > s.height())
    {
        throw std::invalid_argument("Invalid ROI dimensions");
    }
    Image roi(w, h);
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            *(*(roi.data + i) + j) = *(*(data + y + i) + x + j);
        }
    }
    return roi;
}

Image Image::ROI(const Rectangle &r) const
{
    return ROI(r.top_left.x, r.top_left.y, r.width, r.height);
}

Image Image::zeros(int w, int h)
{
    Image img(w, h);
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            img.data[i][j] = 0;
        }
    }
    return img;
}

Image Image::ones(int w, int h)
{
    Image img(w, h);
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            img.data[i][j] = 1;
        }
    }
    return img;
}

int Image::max_value()
{
    int max_val = 0;
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            if (data[i][j] > max_val)
            {
                max_val = data[i][j];
            }
        }
    }
    return max_val;
}