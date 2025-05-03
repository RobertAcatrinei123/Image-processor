#pragma once
#include "image.h"

class ImageProcessing
{
public:
    virtual void process(const Image &src, Image &dest) = 0;
};

class BrightnessContrast : public ImageProcessing
{
private:
    double b;
    double a;

public:
    BrightnessContrast() : b(0), a(1) {};
    BrightnessContrast(double alpha, double beta);
    void process(const Image &src, Image &dest) override;
};

class GammaCorrection : public ImageProcessing
{
private:
    double gamma;

public:
    GammaCorrection() : gamma(1) {};
    GammaCorrection(double g);
    void process(const Image &src, Image &dest) override;
};

enum class ConvolutionType
{
    Identity,
    MeanBlur,
    GaussianBlur,
    HorizontalSobel,
    VerticalSobel,
};

class Convolution : public ImageProcessing
{
private:
    int (*scalar)(int) = nullptr;
    double kernel[3][3];

public:
    Convolution();
    Convolution(ConvolutionType type);
    void process(const Image &src, Image &dest) override;
};