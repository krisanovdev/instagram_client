#pragma once
#include "IInstagramAuthenticator.h"
#include "ISSLQuery.h"

class InstagramAuthenticator : public IInstagramAuthenticator
{
public:
    InstagramAuthenticator(const std::string& username, const std::string& password);
    virtual void PerformLogin(std::string& csrfToken) override;

private:
    static void ConfigureQuery(ISSLQuery* query);
    static void CheckAuthenticantion(const std::string& response);

private:
    std::string m_username;
    std::string m_password;
};
