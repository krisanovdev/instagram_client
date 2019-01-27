#include <string>
#include <iostream>
#include <memory>
#include "InstagramAuthenticator.h"

int main(void)
{
    std::unique_ptr<IInstagramAuthenticator> auth = std::make_unique<InstagramAuthenticator>("", "");
    std::string token;
    auth->PerformLogin(token);

    return 0;
}