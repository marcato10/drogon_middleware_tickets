//
// Created by marcato on 20/10/24.
//
#include "PersonRepository.hpp"
using namespace Middleware;


drogon::Task<std::optional<Pessoa>> PersonRepository::getPessoaByLoginCoro(std::string login, Json::Value &out) {
    auto request = co_await this->proxyClient->getCoro("/usuarios/login/"+login);
    if(request.body.has_value()){
        Pessoa pessoa = Pessoa::fromJson(request.body.value());
        out = std::move(request.body.value());
        co_return pessoa;
    }
    co_return std::nullopt;
}

drogon::Task<ServerResponse> PersonRepository::createPessoaCoro(Pessoa pessoa) {
    Json::Value value = pessoa.toJson(pessoa);
    auto request = co_await this->proxyClient->postCoro("/usuarios",value);
    co_return request;
}
/*
drogon::Task<ServerResponse> PersonRepository::updatePessoaCoro(Pessoa pessoa) {
    return nullptr;
}
*/



