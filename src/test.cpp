#include "test.h"
#include "image.h"
#include "reader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include "imgprocessing.h"

void testAll()
{
    testIOFunctions();
    testIOStream();
    testOperators();
    testImageProcessing();
}

void testIOFunctions()
{
    Image img1;
    img1.load("saturn.ascii.pgm");
    img1.save("saturn_out.ascii.pgm");
}

void testIOStream()
{
    std::ifstream ifs("saturn.ascii.pgm");
    if (!ifs.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    Image img;
    ifs >> img;
    std::ofstream ofs("saturn_out.ascii.pgm");
    if (!ofs.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    ofs << img;
    ofs.close();
    ifs.close();
}

void testOperators()
{
    Image img1(100, 100);
    img1.load("saturn.ascii.pgm");
    Image img2(img1);
    assert(img1 == img2);
    Image img3 = img1 + img2;
    assert(img3 != img1);
    Image img4;
    img4 = img1 * 2;
    assert(img4 != img1);
    assert(img4 == img3);
    img1 *= 2;
    assert(img1 == img4);
    img1 += img2;
    assert(img1 != img2);
    img1 -= img2;
    img1 = Image::zeros(100, 100);
    img2 = Image::ones(100, 100);
    img1 += img2;
    assert(img1 == img2);
    img1 = img1 - img2;
    assert(img1 == Image::zeros(100, 100));
    img1 = img1 + 1;
    assert(img1 == img2);
    img1 = img1 - 1 + 1;
    assert(img1 == img2);
    img1 -= 1;
    img1 += 1;
    assert(img1 == img2);
}

void testImageProcessing()
{
    Image img1(100, 100);
    img1.load("saturn.ascii.pgm");
    Image img2(img1);
    BrightnessContrast bc(1.5, 0.5);
    bc.process(img1, img2);
    img2.save("saturn_out_brightness_contrast.pgm");
    GammaCorrection gc(2.2);
    gc.process(img1, img2);
    img2.save("saturn_out_gamma_correction.pgm");
    Convolution conv1(ConvolutionType::Identity);
    conv1.process(img1, img2);
    img2.save("saturn_out_identity.pgm");
    Convolution conv2(ConvolutionType::MeanBlur);
    conv2.process(img1, img2);
    img2.save("saturn_out_mean_blur.pgm");
    Convolution conv3(ConvolutionType::GaussianBlur);
    conv3.process(img1, img2);
    img2.save("saturn_out_gaussian_blur.pgm");
    Convolution conv4(ConvolutionType::HorizontalSobel);
    conv4.process(img1, img2);
    img2.save("saturn_out_horizontal_sobel.pgm");
    Convolution conv5(ConvolutionType::VerticalSobel);
    conv5.process(img1, img2);
    img2.save("saturn_out_vertical_sobel.pgm");
}