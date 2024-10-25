#ifndef MIDDLEWARE_PROXY_CLIENT_HPP
#define MIDDLEWARE_PROXY_CLIENT_HPP
#include <drogon/drogon.h>
#include <drogon/HttpClient.h>
#include <drogon/HttpTypes.h>
#include <drogon/HttpResponse.h>
#include <future>
#include <iostream>

using namespace drogon;
namespace Middleware {
    struct ServerResponse {
        HttpStatusCode responseCode;
        std::optional<Json::Value> body;
    };

    class ProxyClient {
    private:
        std::unique_ptr<Json::CharReader> jsonReader;
        std::shared_ptr<HttpClient> httpClient;
    public:
        ProxyClient() : jsonReader(Json::CharReaderBuilder{}.newCharReader()),
        httpClient(HttpClient::newHttpClient("http://127.0.0.1:3000")) {};
        drogon::Task<ServerResponse> getCoro(const std::string& path);
        drogon::Task<ServerResponse> postCoro(const std::string& path,const Json::Value& body);
        drogon::Task<ServerResponse> putCoro(const std::string& path,const Json::Value& data);
        //drogon::Task<ServerResponse> delCoro(const std::string& path);

        std::optional<Json::Value>stringToJson(const std::string& body);
    };
};

#endif //MIDDLEWARE_PROXY_CLIENT_HPP
