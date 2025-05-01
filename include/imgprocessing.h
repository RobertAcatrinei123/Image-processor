#pragma once
#include "image.h"

class ImageProcessing
{
public:
    virtual void process(const Image &src,Image &dest) = 0;
};