//
// Created by marcato on 20/10/24.
//

#ifndef MIDDLEWARE_PERSONCONTROLLER_HPP
#define MIDDLEWARE_PERSONCONTROLLER_HPP

#include <drogon/drogon.h>
#include "../repository/PersonRepository.hpp"
#include <drogon/utils/coroutine.h>
namespace user{
class PersonController : public drogon::HttpController<PersonController,false>{
private:
    std::shared_ptr<Middleware::PersonRepository>personRepository;

public:
   explicit PersonController(std::shared_ptr<Middleware::PersonRepository> perRep) : personRepository(std::move(perRep)){};
   PersonController() : personRepository(std::make_shared<Middleware::PersonRepository>()){};
   auto getUserByLogin(HttpRequestPtr req,std::function<void(const drogon::HttpResponsePtr&)> callback,std::string login)->drogon::Task<>;
   auto createUser(HttpRequestPtr req,std::function<void(const drogon::HttpResponsePtr&)> callback)->drogon::Task<>;
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(PersonController::getUserByLogin,"/user/{login}",HttpMethod::Post);
        ADD_METHOD_TO(PersonController::createUser,"/register",HttpMethod::Post);
    METHOD_LIST_END


};

};
#endif //MIDDLEWARE_PERSONCONTROLLER_HPP
