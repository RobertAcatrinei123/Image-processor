#include <string>
#include <fstream>

class Reader
{
private:
    std::istream &ifs;
    std::string buffer;
    int bufferIndex = 0;
    void next();

public:
    Reader(const std::istream &ifs);
    int nextInt();
};