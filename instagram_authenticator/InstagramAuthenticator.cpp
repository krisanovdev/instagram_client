#include <memory>
#include "InstagramAuthenticator.h"
#include "SSLQuery.h"
#include "AuthorizationUtils.h"

InstagramAuthenticator::InstagramAuthenticator(const std::string& username, const std::string& password)
    : m_username(username)
    , m_password(password)
{
}

void InstagramAuthenticator::PerformLogin(std::string& csrfToken)
{
    std::unique_ptr<ISSLQuery> query = std::make_unique<SSLQuery>();
    ConfigureQuery(query.get());
    authorization::utils::SetBasicHeaders(query.get());
    authorization::utils::SetCSRFToken(query.get(), "1");
    query->SetPostField("username", m_username);
    query->SetPostField("password", m_password);
    query->SetPostField("queryParams", "{\"source\":\"auth_switcher\"}"); // TO DO : implement special symbols replacing
    std::string buffer;
    query->GetData("https://www.instagram.com/accounts/login/ajax/", buffer);
    Cookies_vt cookies;
    query->GetCookies(cookies);

    for (auto it = cookies.begin(); it != cookies.end(); it++)
    {
        if (it->first == "csrftoken" && !(it->second.empty()) && it->second != "\"\"")
        {
            csrfToken = it->second;
            return;
        }
    }
}

void InstagramAuthenticator::ConfigureQuery(ISSLQuery* query)
{
    query->SetProxy("localhost", 8888);
    query->EnableSSLVerification(false);
    query->FollowLocation(true);
}
