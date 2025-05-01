#include "image.h"
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    Image img1;
    img1.load("saturn.ascii.pgm");
    Image img2;
    img2.load("saturn.ascii.pgm");
    Image img3 = img1 + img2;
    img3.save("saturn_out.ascii.pgm");
}