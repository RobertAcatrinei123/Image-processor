#include <string>
#include <fstream>

/**
 * @class Reader
 * @brief Utility class for reading integers from a stream, skipping comments and whitespace.
 */
class Reader
{
private:
    std::istream &ifs;   ///< Input stream
    std::string buffer;  ///< Current buffer line
    int bufferIndex = 0; ///< Index in buffer
    /**
     * @brief Reads the next line from the stream into the buffer.
     */
    void next();

public:
    /**
     * @brief Constructs a Reader for the given input stream.
     * @param ifs Input stream
     */
    Reader(const std::istream &ifs);
    /**
     * @brief Reads the next integer from the stream, skipping comments and whitespace.
     * @return The next integer
     */
    int nextInt();
};