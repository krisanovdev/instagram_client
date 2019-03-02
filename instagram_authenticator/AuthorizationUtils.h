#pragma once
#include "ISSLQuery.h"

namespace authorization
{
    struct AuthResponse
    {
        bool isAuthenticated;
        bool isUser;
        std::string userId;
        bool isOneTapPrompt;
        std::string fr; // TO DO : Research this field
        bool isReactivated;
        std::string status;
    };

    namespace utils
    {
        void SetBasicHeaders(ISSLQuery* query);
        void SetCSRFToken(ISSLQuery* query, const std::string& token);
        void ParseAuthResponse(const std::vector<char>& rawJson, AuthResponse& output);
    }
}