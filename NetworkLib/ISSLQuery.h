#pragma once
#include <string>
#include <map>
#include <vector>

using Cookie = std::pair<std::string, std::string>;
using Cookies_vt = std::vector<Cookie>;

class ISSLQuery
{
public:
    virtual ~ISSLQuery(){}
    virtual void GetData(const std::string& url, std::string& buffer) = 0;
    virtual void SetHeader(const std::string& key, const std::string& value) = 0;
    virtual void SetPostField(const std::string& field, const std::string& value) = 0;
    virtual void SetProxy(const std::string& host, int port) = 0;
    virtual void EnableSSLVerification(bool enable) = 0;
    virtual void FollowLocation(bool follow) = 0;
    virtual void GetCookies(Cookies_vt& cookies) = 0;
};