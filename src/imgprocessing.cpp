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