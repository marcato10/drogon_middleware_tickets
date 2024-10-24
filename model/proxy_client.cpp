//
// Created by marcato on 19/10/24.
//

#include "proxy_client.hpp"

std::optional<Json::Value> Middleware::ProxyClient::stringToJson(const std::string &body) {
    if(body.empty()){
        return std::nullopt;
    }
    Json::Value jValue;
    std::string errors;
    bool parsingError = this->jsonReader->parse(
            body.c_str(),
            body.c_str() + body.size(),
            &jValue,
            &errors
    );
    if(!parsingError){
        std::cerr << "Json Parsing error: "<< errors << std::endl;
        return std::nullopt;
    }
    return jValue;
}

drogon::Task<Middleware::ServerResponse>
Middleware::ProxyClient::getCoro(const std::string &path) {
    auto request = HttpRequest::newHttpRequest();
    request->setMethod(HttpMethod::Get);
    request->setPath(path);

    auto result = co_await this->httpClient->sendRequestCoro(request);
    ServerResponse serverResponse;
    std::optional<Json::Value> jValue = this->stringToJson(result->getBody().data());
    std::cout << result->getBody().data() << std::endl;

    serverResponse.responseCode = result->getStatusCode();
    serverResponse.body = jValue;
    co_return serverResponse;
}

drogon::Task<Middleware::ServerResponse>
Middleware::ProxyClient::postCoro(const std::string &path, const Json::Value &body) {
    auto request = HttpRequest::newHttpJsonRequest(body);
    request->setMethod(HttpMethod::Post);
    request->setPath(path);
    auto result = co_await this->httpClient->sendRequestCoro(request);
    ServerResponse serverResponse;
    std::optional<Json::Value> jValue = this->stringToJson(result->getBody().data());
    std::cout << result->getBody().data() << std::endl;

    serverResponse.responseCode = result->getStatusCode();
    serverResponse.body = jValue;
    co_return serverResponse;
}

drogon::Task<Middleware::ServerResponse>
Middleware::ProxyClient::putCoro(const std::string &path, const Json::Value &data) {
    auto request = HttpRequest::newHttpJsonRequest(data);
    request->setPath(path);
    request->setMethod(HttpMethod::Put);
    auto result = co_await this->httpClient->sendRequestCoro(request);
    ServerResponse serverResponse;
    std::optional<Json::Value> jValue = this->stringToJson(result->getBody().data());
    std::cout << result->getBody().data() << std::endl;

    serverResponse.responseCode = result->getStatusCode();
    serverResponse.body = jValue;
    co_return serverResponse;
}

