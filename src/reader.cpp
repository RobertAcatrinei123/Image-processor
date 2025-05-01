#include "reader.h"
#include <iostream>
#include <fstream>

Reader::Reader(const std::istream &ifs) : ifs(const_cast<std::istream &>(ifs))
{
    next();
}

void Reader::next()
{
    std::getline(ifs, buffer);
    bufferIndex = 0;
}

int Reader::nextInt()
{
    while (true)
    {
        if (bufferIndex >= buffer.size())
        {
            next();
        }
        else if (buffer[bufferIndex] == '#')
        {
            next();
        }
        else if (buffer[bufferIndex] >= '0' && buffer[bufferIndex] <= '9')
        {
            int emptyIndex = buffer.find(" ", bufferIndex);
            std::string sstr = buffer.substr(bufferIndex, emptyIndex - bufferIndex);
            bufferIndex = emptyIndex;
            int val = std::stoi(sstr);
            return val;
        }
        else
        {
            bufferIndex++;
        }
    }
}