#include "SSLQuery.h"

namespace
{
    static size_t CurlCallback(char* ptr, size_t size, size_t nmemb, std::string* stream)
    {
        stream->append(ptr, size * nmemb);
        return size * nmemb;
    }
}

SSLQuery::SSLQuery()
    : m_curl(curl_easy_init())
{
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &CurlCallback);

    const char* cookieFile = "cookies.txt";
    curl_easy_setopt(m_curl, CURLOPT_COOKIEJAR, cookieFile);
    curl_easy_setopt(m_curl, CURLOPT_COOKIEFILE, cookieFile);
}

SSLQuery::~SSLQuery()
{
    curl_easy_cleanup(m_curl);
    curl_slist_free_all(m_headers);
}

void SSLQuery::GetData(const std::string& url, std::string& buffer)
{
    std::string().swap(buffer);
    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headers);

    if (!m_queryString.empty())
    {
        curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, m_queryString.c_str());
    }

    curl_easy_perform(m_curl);
}

void SSLQuery::SetHeader(const std::string& key, const std::string& value)
{
    const std::string header = key + ": " + value;
    m_headers = curl_slist_append(m_headers, header.c_str());
}

void SSLQuery::SetPostField(const std::string& field, const std::string& value)
{
    if (!m_queryString.empty())
    {
        m_queryString += '&';
    }

    m_queryString +=  value;
}

void SSLQuery::SetProxy(const std::string& host, int port)
{
    curl_easy_setopt(m_curl, CURLOPT_PROXY, host.c_str());
    curl_easy_setopt(m_curl, CURLOPT_PROXYPORT, port);
}

void SSLQuery::EnableSSLVerification(bool enable)
{
    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, enable);
    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, enable);
}

void SSLQuery::FollowLocation(bool follow)
{
    curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, follow);
}

void SSLQuery::GetCookies(Cookies_vt& cookies)
{
    curl_slist* list = nullptr;
    curl_easy_getinfo(m_curl, CURLINFO_COOKIELIST, &list);

    curl_slist* each = list;
    while (each)
    {
        auto cookie = ParseCoookieFromCurlSlistData(each->data);
        cookies.emplace_back(cookie.first, cookie.second);
        each = each->next;
    }
}

std::pair<std::string, std::string> SSLQuery::ParseCoookieFromCurlSlistData(const std::string& data)
{
    std::pair<std::string, std::string> cookie;
    const size_t lastTab = data.rfind('\t');

    if (lastTab == std::string::npos)
    {
        throw std::runtime_error("Can't parse cookie record");
    }

    cookie.second = data.substr(lastTab + 1);
    const size_t preLastTab = data.rfind('\t', lastTab - 1);

    if (preLastTab == std::string::npos)
    {
        throw std::runtime_error("Can't parse cookie record");
    }

    cookie.first = data.substr(preLastTab + 1, lastTab - preLastTab - 1);
    return cookie;
}
