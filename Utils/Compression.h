#pragma once
#include <vector>

namespace utils
{
    namespace compression
    {
        void GZipDecompress(const char* data, size_t dataSize, std::vector<char>& output, size_t decompessionBound);
    }
}
