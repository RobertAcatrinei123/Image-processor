#include "imgprocessing.h"
#include "image.h"
#include <stdexcept>
#include <cmath>

BrightnessContrast::BrightnessContrast(double alpha, double beta) : a(alpha), b(beta)
{
    if (a < 0)
    {
        throw std::invalid_argument("Alpha must be non-negative");
    }
}

void BrightnessContrast::process(const Image &src, Image &dest)
{
    if (src.empty())
    {
        throw std::invalid_argument("Source image is empty");
    }
    dest = src * a + b;
}

GammaCorrection::GammaCorrection(double g) : gamma(g)
{
    if (gamma <= 0)
    {
        throw std::invalid_argument("Gamma must be positive");
    }
}

void GammaCorrection::process(const Image &src, Image &dest)
{
    if (src.empty())
    {
        throw std::invalid_argument("Source image is empty");
    }
    dest = src;
    for (int y = 0; y < src.height(); ++y)
    {
        for (int x = 0; x < src.width(); ++x)
        {
            dest.at(x, y) = std::clamp((int)std::pow(src.getAt(x, y), gamma), 0, 255);
        }
    }
}

Convolution::Convolution()
{
    kernel[0][0] = 0;
    kernel[0][1] = 0;
    kernel[0][2] = 0;
    kernel[1][0] = 0;
    kernel[1][1] = 1;
    kernel[1][2] = 0;
    kernel[2][0] = 0;
    kernel[2][1] = 0;
    kernel[2][2] = 0;
    scalar = [](int x)
    { return x; };
}

Convolution::Convolution(ConvolutionType type)
{
    switch (type)
    {
    case ConvolutionType::Identity:
        kernel[0][0] = 0;
        kernel[0][1] = 0;
        kernel[0][2] = 0;
        kernel[1][0] = 0;
        kernel[1][1] = 1;
        kernel[1][2] = 0;
        kernel[2][0] = 0;
        kernel[2][1] = 0;
        kernel[2][2] = 0;
        scalar = [](int x)
        { return x; };
        break;
    case ConvolutionType::MeanBlur:
        kernel[0][0] = 1;
        kernel[0][1] = 1;
        kernel[0][2] = 1;
        kernel[1][0] = 1;
        kernel[1][1] = 1;
        kernel[1][2] = 1;
        kernel[2][0] = 1;
        kernel[2][1] = 1;
        kernel[2][2] = 1;
        scalar = [](int x)
        { return x / 9; };
        break;
    case ConvolutionType::GaussianBlur:
        kernel[0][0] = 1;
        kernel[0][1] = 2;
        kernel[0][2] = 1;
        kernel[1][0] = 2;
        kernel[1][1] = 4;
        kernel[1][2] = 2;
        kernel[2][0] = 1;
        kernel[2][1] = 2;
        kernel[2][2] = 1;
        scalar = [](int x)
        { return x / 16; };
        break;
    case ConvolutionType::HorizontalSobel:
        kernel[0][0] = -1;
        kernel[0][1] = 0;
        kernel[0][2] = 1;
        kernel[1][0] = -2;
        kernel[1][1] = 0;
        kernel[1][2] = 2;
        kernel[2][0] = -1;
        kernel[2][1] = 0;
        kernel[2][2] = 1;
        scalar = [](int x)
        {
            x += 4 * 255;
            x /= 8;
            return x;
        };
        break;
    case ConvolutionType::VerticalSobel:
        kernel[0][0] = 1;
        kernel[0][1] = 2;
        kernel[0][2] = 1;
        kernel[1][0] = 0;
        kernel[1][1] = 0;
        kernel[1][2] = 0;
        kernel[2][0] = -1;
        kernel[2][1] = -2;
        kernel[2][2] = -1;
        scalar = [](int x)
        {
            x += 4 * 255;
            x /= 8;
            return x;
        };
        break;
    }
}

void Convolution::process(const Image &src, Image &dest)
{
    if (src.empty())
    {
        throw std::invalid_argument("Source image is empty");
    }

    dest = src;

    for (int y = 0; y < src.height(); ++y)
    {
        for (int x = 0; x < src.width(); ++x)
        {
            int sum = 0;
            for (int ky = -1; ky <= 1; ++ky)
            {
                for (int kx = -1; kx <= 1; ++kx)
                {
                    sum += kernel[ky + 1][kx + 1] * src.getAt(x + kx, y + ky, true);
                }
            }
            dest.at(x, y) = scalar(sum);
        }
    }
}