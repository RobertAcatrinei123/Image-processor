#include "image.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "reader.h"

Size::Size() : w(0), h(0) {}
Size::Size(int w, int h) : w(w), h(h) {}
int Size::width() const { return w; }
int Size::height() const { return h; }
Image::Image() : s(0, 0), data(nullptr) {}

bool Size::operator==(const Size &other) const
{
    return w == other.w && h == other.h;
}

bool Size::operator!=(const Size &other) const
{
    return !(*this == other);
}

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
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        return false;
    }
    ofs << "P2\n";
    ofs << s.width() << " " << s.height() << "\n";
    ofs << int(max_value) << "\n";
    int ind = 0;
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            ofs << std::setw(3) << int(data[i][j]) << " ";
            ind++;
            if (ind != 0 && ind % 17 == 0)
            {
                ofs << "\n";
            }
        }
    }
    return true;
}

bool Image::load(const std::string &filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        return false;
    }
    std::string magic_number;
    std::getline(ifs, magic_number);
    if (magic_number[0] != 'P' || magic_number[1] != '2')
    {
        throw std::invalid_argument("Invalid image format");
    }
    Reader reader(ifs);
    int w = reader.nextInt();
    // std::cerr << "w: " << w << std::endl;
    int h = reader.nextInt();
    // std::cerr << "h: " << h << std::endl;
    max_value = reader.nextInt();
    // std::cerr << "max_val: " << max_val << std::endl;
    if (w <= 0 || h <= 0 || max_value <= 0)
    {
        throw std::invalid_argument("Invalid image dimensions or max value");
    }
    release();
    s = Size(w, h);
    data = new unsigned char *[h];
    for (int i = 0; i < h; ++i)
    {
        data[i] = new unsigned char[w];
        for (int j = 0; j < w; ++j)
        {
            int val = reader.nextInt();
            // std::cerr << "val: " << val << std::endl;
            data[i][j] = (unsigned char)(val);
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const Image &img)
{
    os << "P2\n";
    os << img.s.width() << " " << img.s.height() << "\n";
    os << int(img.max_value) << "\n";
    int ind = 0;
    for (int i = 0; i < img.height(); ++i)
    {
        for (int j = 0; j < img.width(); ++j)
        {
            os << std::setw(3) << int(img.data[i][j]) << " ";
            ind++;
            if (ind != 0 && ind % 17 == 0)
            {
                os << "\n";
            }
        }
    }
    return os;
}

std::istream &operator>>(std::istream &is, Image &img)
{
    std::string magic_number;
    std::getline(is, magic_number);
    if (magic_number[0] != 'P' || magic_number[1] != '2')
    {
        throw std::invalid_argument("Invalid image format");
    }
    Reader reader(is);
    int w = reader.nextInt();
    int h = reader.nextInt();
    img.max_value = reader.nextInt();
    if (w <= 0 || h <= 0 || img.max_value <= 0)
    {
        throw std::invalid_argument("Invalid image dimensions or max value");
    }
    img.release();
    img.s = Size(w, h);
    img.data = new unsigned char *[h];
    for (int i = 0; i < h; ++i)
    {
        img.data[i] = new unsigned char[w];
        for (int j = 0; j < w; ++j)
        {
            int val = reader.nextInt();
            img.data[i][j] = (unsigned char)(val);
        }
    }
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

            result.data[i][j] = std::clamp((int)data[i][j] + (int)other.data[i][j], 0, 255);
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
            result.data[i][j] = std::clamp((int)data[i][j] - (int)other.data[i][j], 0, 255);
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
            data[i][j] = std::clamp((int)data[i][j] + (int)other.data[i][j], 0, 255);
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
            data[i][j] = std::clamp((int)data[i][j] - (int)other.data[i][j], 0, 255);
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
            result.data[i][j] = std::clamp((int)data[i][j] * scalar, 0, 255);
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
            result.data[i][j] = std::clamp((int)data[i][j] + scalar, 0, 255);
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
            result.data[i][j] = std::clamp((int)data[i][j] - scalar, 0, 255);
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
            data[i][j] = std::clamp(int(data[i][j]) + scalar, 0, 255);
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
            data[i][j] = std::clamp(int(data[i][j]) - scalar, 0, 255);
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
            data[i][j] = std::clamp(int(data[i][j]) * scalar, 0, 255);
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

unsigned char Image::getAt(int x, int y) const
{
    if (x < 0 || x >= s.width() || y < 0 || y >= s.height())
    {
        throw std::out_of_range("Index out of range");
    }
    return data[y][x];
}

unsigned char Image::getAt(const Point &p) const
{
    return getAt(p.x, p.y);
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

bool Image::operator==(const Image &other) const
{
    if (s != other.s)
    {
        return false;
    }

    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            if (data[i][j] != other.data[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool Image::operator!=(const Image &other) const
{
    return !(*this == other);
}