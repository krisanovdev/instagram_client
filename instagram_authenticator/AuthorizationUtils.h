#pragma once
#include "ISSLQuery.h"

namespace authorization
{
    namespace utils
    {
        void SetBasicHeaders(ISSLQuery* query);
        void SetCSRFToken(ISSLQuery* query, const std::string& token);
    }
}