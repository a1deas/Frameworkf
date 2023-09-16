#include <fstream>

#include "Core/log.h"
#include "file.h"

namespace Ff
{
    std::string readFileToString(const std::string& path)
    {
        std::ifstream fileObject(path);
        if (!fileObject.is_open())
        {
            FFFATAL("failed open file: {}", path);
            abort();
        }

        std::stringstream ss;
        ss << fileObject.rdbuf();

        return ss.str();
    }

    void writeStringToFile(const std::string& path, const std::string& stringToWrite)
    {
        std::ofstream fileObject(path);
        if (!fileObject.is_open())
        {
            FFFATAL("failed open file: {}", path);
            abort();
        }

        fileObject << stringToWrite;
        fileObject.flush();
    }

    std::vector<std::byte> readBinaryFile(const std::string& path)
    {
        std::ifstream fileObject(path, std::ifstream::binary | std::ifstream::ate);

        if (!fileObject.is_open())
        {
            FFFATAL("failed open file: {}", path);
            abort();
        }

        uint64_t fileSize = fileObject.tellg();
        fileObject.seekg(0);

        std::vector<std::byte> byteVector;
        byteVector.resize(fileSize);
        fileObject.read(reinterpret_cast<char*>(byteVector.data()), fileSize);
        return byteVector;
    }

    void writeToBinaryFile(const std::string& path, const void* data, uint64_t size)
    {
        std::ofstream fileObject(path, std::ofstream::binary);

        if (!fileObject.is_open())
        {
            FFFATAL("failed open file: {}", path);
            abort();
        }

        fileObject.write(reinterpret_cast<const char*>(data), size);
        fileObject.flush();
    }

} // namespace Ff