#pragma once
#include "image.h"

/**
 * @class ImageProcessing
 * @brief Abstract base class for image processing operations.
 */
class ImageProcessing
{
public:
    /**
     * @brief Processes the source image and writes the result to dest.
     * @param src Source image
     * @param dest Destination image
     */
    virtual void process(const Image &src, Image &dest) = 0;
};

/**
 * @class BrightnessContrast
 * @brief Adjusts brightness and contrast of an image.
 */
class BrightnessContrast : public ImageProcessing
{
private:
    double b; ///< Brightness
    double a; ///< Contrast

public:
    /**
     * @brief Default constructor. No adjustment.
     */
    BrightnessContrast() : b(0), a(1) {};
    /**
     * @brief Constructs with given contrast and brightness.
     * @param alpha Contrast
     * @param beta Brightness
     */
    BrightnessContrast(double alpha, double beta);
    /**
     * @brief Processes the image with brightness/contrast adjustment.
     * @param src Source image
     * @param dest Destination image
     */
    void process(const Image &src, Image &dest) override;
};

/**
 * @class GammaCorrection
 * @brief Applies gamma correction to an image.
 */
class GammaCorrection : public ImageProcessing
{
private:
    double gamma; ///< Gamma value

public:
    /**
     * @brief Default constructor. Gamma = 1.
     */
    GammaCorrection() : gamma(1) {};
    /**
     * @brief Constructs with given gamma value.
     * @param g Gamma value
     */
    GammaCorrection(double g);
    /**
     * @brief Processes the image with gamma correction.
     * @param src Source image
     * @param dest Destination image
     */
    void process(const Image &src, Image &dest) override;
};

/**
 * @enum ConvolutionType
 * @brief Types of convolution kernels.
 */
enum class ConvolutionType
{
    Identity,        ///< Identity kernel
    MeanBlur,        ///< Mean blur kernel
    GaussianBlur,    ///< Gaussian blur kernel
    HorizontalSobel, ///< Horizontal Sobel kernel
    VerticalSobel,   ///< Vertical Sobel kernel
};

/**
 * @class Convolution
 * @brief Applies a convolution filter to an image.
 */
class Convolution : public ImageProcessing
{
private:
    int (*scalar)(int) = nullptr; ///< Optional scalar function
    double kernel[3][3];          ///< Convolution kernel

public:
    /**
     * @brief Default constructor.
     */
    Convolution();
    /**
     * @brief Constructs with a specific convolution type.
     * @param type Convolution kernel type
     */
    Convolution(ConvolutionType type);
    /**
     * @brief Processes the image with convolution.
     * @param src Source image
     * @param dest Destination image
     */
    void process(const Image &src, Image &dest) override;
};