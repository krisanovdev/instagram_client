#include "AuthorizationUtils.h"

void authorization::utils::SetBasicHeaders(ISSLQuery* query)
{
    query->SetHeader("x-instagram-ajax", "e804ac7f6fd6");
    query->SetHeader("accept", "*/*");
    query->SetHeader("x-requested-with", "XMLHttpRequest");
    query->SetHeader("user-agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36 OPR/58.0.3135.47");
    query->SetHeader("referer", "https://www.instagram.com/accounts/login/?source=auth_switcher");
    query->SetHeader("accept-encoding", "gzip, deflate, br");
    query->SetHeader("accept-language", "en-US,en;q=0.9");
}

void authorization::utils::SetCSRFToken(ISSLQuery* query, const std::string& token)
{
    query->SetHeader("x-csrftoken", token.c_str());
}
