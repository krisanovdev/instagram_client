#pragma once
#include <string>

class IInstagramAuthenticator
{
public:
    virtual ~IInstagramAuthenticator(){}
    virtual void PerformLogin(std::string& csrfToken) = 0;
};