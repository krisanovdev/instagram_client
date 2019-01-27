#pragma once
#include "vector"
#include "ISSLQuery.h"
#include "curl\curl.h"

class SSLQuery : public ISSLQuery
{
public:
    SSLQuery();
    ~SSLQuery();
    virtual void GetData(const std::string& url, std::string& buffer) override;
    virtual void SetHeader(const std::string& key, const std::string& value) override;
    virtual void SetPostField(const std::string& field, const std::string& value) override;
    virtual void SetProxy(const std::string& host, int port) override;
    virtual void EnableSSLVerification(bool enable) override;
    virtual void FollowLocation(bool follow) override;
    virtual void GetCookies(Cookies_vt& cookies) override;

private:
    Cookie ParseCoookieFromCurlSlistData(const std::string& data);

private:
    CURL* m_curl;
    curl_slist* m_headers;
    std::string m_queryString;
};