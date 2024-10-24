//
// Created by marcato on 20/10/24.
//

#ifndef MIDDLEWARE_PERSONREPOSITORY_HPP
#define MIDDLEWARE_PERSONREPOSITORY_HPP


#include "person.hpp"
#include "proxy_client.hpp"
#include <memory>
#include <drogon/drogon.h>
namespace Middleware{
    class PersonRepository{
private:
    std::shared_ptr<Middleware::ProxyClient>proxyClient;
public:

    PersonRepository() : proxyClient(std::make_shared<ProxyClient>()) {}
    explicit PersonRepository(const std::shared_ptr<ProxyClient>&proxy) : proxyClient(proxy) {}
    drogon::Task<std::optional<Pessoa>> getPessoaByLoginCoro(std::string login,Json::Value& out);
    drogon::Task<ServerResponse> createPessoaCoro(Pessoa pessoa);
    drogon::Task<ServerResponse> updatePessoaCoro(Pessoa pessoa);

};
};

#endif //MIDDLEWARE_PERSONREPOSITORY_HPP
