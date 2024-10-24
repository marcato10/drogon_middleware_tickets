//
// Created by marcato on 20/10/24.
//

#include "PersonController.hpp"
using namespace user;

auto PersonController::getUserByLogin(HttpRequestPtr req, std::function<void(const drogon::HttpResponsePtr &)> callback,
                                      std::string login) -> drogon::Task<> {
    try{
        Json::Value outputJson;
        auto proxyResponse = co_await this->personRepository->getPessoaByLoginCoro(login,outputJson);
        if(proxyResponse.has_value()){
            auto response = HttpResponse::newHttpJsonResponse(outputJson);
            response->setStatusCode(k200OK);
            callback(response);
            co_return;
        }
        auto response = HttpResponse::newHttpResponse();
        response->setStatusCode(k204NoContent);
        callback(response);
        co_return;
    }
    catch (const std::exception &e)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        std::cerr << "Error:" << e.what() << std::endl;
        resp->setBody(e.what());
        callback(resp);
    }
    co_return;
}

auto PersonController::createUser(HttpRequestPtr req, std::function<void(const drogon::HttpResponsePtr &)> callback) -> drogon::Task<> {
    try{
        if(req == nullptr){
            throw std::exception();
        }
        auto reqBody = *(req->getJsonObject());

        Pessoa pessoa = Pessoa::fromJson(reqBody);
        std::cout << pessoa.getLogin().login << std::endl;
        auto result = co_await this->personRepository->createPessoaCoro(Pessoa::fromJson(reqBody));
        auto response = HttpResponse::newHttpJsonResponse(result.body.value());
        response->setStatusCode(result.responseCode);
        callback(response);
    }
    catch (const std::exception &e)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        std::cerr << "Error:" << e.what() << std::endl;
        resp->setBody(e.what());
        callback(resp);
    }
    co_return;
}


