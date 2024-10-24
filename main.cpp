#include <iostream>
#include <drogon/drogon.h>
#include "proxy_client.hpp"
#include <memory>
#include "PersonController.hpp"
#include "TicketController.hpp"
const std::string& middleware_ip = "127.0.0.1";

int main() {
    trantor::Logger::setLogLevel(trantor::Logger::kTrace);
    auto proxyClient = std::make_shared<Middleware::ProxyClient>();

    drogon::app().addListener(middleware_ip,8000);
    drogon::app().registerController(std::make_shared<user::PersonController>());
    drogon::app().registerController(std::make_shared<ticket::TicketController>());
    drogon::app().run();
    LOG_INFO << "Server running on 127.0.0.1:8080";
    LOG_INFO << drogon::app().getHandlersInfo().data();

    return 0;
}
