#include "image.h"
#include <math.h>
#include <iostream>
#include <fstream>

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
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        return false;
    }
    ofs << "P2\n";
    ofs << s.width() << " " << s.height() << "\n";
    ofs << this->max_value() << "\n";
    std::setw(3);
    for (int i = 0; i < s.height(); ++i)
    {
        for (int j = 0; j < s.width(); ++j)
        {
            ofs << static_cast<int>(data[i][j]) << " ";
            if ((i * s.width() + j) % 17 == 0 && !(j == 0 && i == 0))
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
    char m[2];
    if (ifs.peek() == '#')
    {
        std::string comment;
        std::getline(ifs, comment);
    }
    ifs >> m[0];
    if(ifs.peek() == '#')
    {
        std::string comment;
        std::getline(ifs, comment);
    }
    ifs >> m[1];
    if (m[0] != 'P' || m[1] != '2')
    {
        return false;
    }
    int max_val, w, h;
    if(ifs.peek() == '#')
    {
        std::string comment;
        std::getline(ifs, comment);
    }
    ifs >> w ;
    if(ifs.peek() == '#')
    {
        std::string comment;
        std::getline(ifs, comment);
    }
    ifs >> h ;
    if(ifs.peek() == '#')
    {
        std::string comment;
        std::getline(ifs, comment);
    }
    ifs >> max_val;
    if (w <= 0 || h <= 0 || max_val <= 0)
    {
        return false;
    }
    release();
    s = Size(w, h);
    data = new unsigned char *[h];
    for (int i = 0; i < h; ++i)
    {
        data[i] = new unsigned char[w];
        for (int j = 0; j < w; ++j)
        {
            if(ifs.peek() == '#')
            {
                std::string comment;
                std::getline(ifs, comment);
            }
            int val;
            ifs >> val;
            data[i][j] = static_cast<unsigned char>(val);
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const Image &img)
{
    os << "P2\n";
    os << img.s.width() << " " << img.s.height() << "\n";
    os << img.max_value() << "\n";
    for (int i = 0; i < img.s.height(); ++i)
    {
        for (int j = 0; j < img.s.width(); ++j)
        {
            os << static_cast<int>(img.data[i][j]) << " ";
            if ((i * img.s.width() + j) % 17 == 0 && !(j == 0 && i == 0))
            {
                os << "\n";
            }
        }
    }
    return os;
}

std::istream &operator>>(std::istream &is, Image &img)
{
    char m[2];
    if (is.peek() == '#')
    {
        std::string comment;
        std::getline(is, comment);
    }
    is >> m[0];
    if (is.peek() == '#')
    {
        std::string comment;
        std::getline(is, comment);
    }
    is >> m[1];
    if (m[0] != 'P' || m[1] != '2')
    {
        throw std::invalid_argument("Invalid image format");
    }
    int max_val, w, h;
    if (is.peek() == '#')
    {
        std::string comment;
        std::getline(is, comment);
    }
    is >> w;
    if (is.peek() == '#')
    {
        std::string comment;
        std::getline(is, comment);
    }
    is >> h;
    if (is.peek() == '#')
    {
        std::string comment;
        std::getline(is, comment);
    }
    is >> max_val;
    if (w <= 0 || h <= 0 || max_val <= 0)
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
            if (is.peek() == '#')
            {
                std::string comment;
                std::getline(is, comment);
            }
            int val;
            is >> val;
            img.data[i][j] = static_cast<unsigned char>(val);
        }
    }
    if (is.fail())
    {
        img.release();
        throw std::runtime_error("Error reading image data");
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

int Image::max_value() const
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