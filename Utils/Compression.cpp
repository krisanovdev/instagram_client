#include <zlib.h>
#include "Compression.h"

void utils::compression::GZipDecompress(const char* data, size_t dataSize, std::vector<char>& output, size_t decompressionBound)
{
    output.resize(decompressionBound);
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = stream.total_in = dataSize;
    stream.next_in = (Bytef*)data;
    stream.avail_out = decompressionBound;
    stream.next_out = (Bytef*)output.data();

    int err = inflateInit2(&stream, 16 + MAX_WBITS);

    if (err == Z_OK)
    {
        err = inflate(&stream, Z_FINISH);
    }

    output.resize(stream.total_out);
}
