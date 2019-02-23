#include <string>
#include <iostream>
#include <memory>
#include "InstagramAuthenticator.h"

int main(void)
{
    std::string username, password;
    std::cin >> username >> password;
    std::unique_ptr<IInstagramAuthenticator> auth = std::make_unique<InstagramAuthenticator>(username, password);
    std::string token;
    auth->PerformLogin(token);

    return 0;
}