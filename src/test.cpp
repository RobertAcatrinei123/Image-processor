#include "test.h"
#include "image.h"
#include "reader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

void testAll()
{
    testIOFunctions();
    testIOStream();
    testOperators();
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