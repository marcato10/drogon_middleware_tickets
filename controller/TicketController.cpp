//
// Created by marcato on 24/10/24.
//

#include "TicketController.hpp"
using namespace ticket;
auto TicketController::getAllTickets(HttpRequestPtr req, std::function<void(
        const drogon::HttpResponsePtr &)> callback) -> drogon::Task<> {
        try{
            Json::Value outputJson;
            auto proxyResponse = co_await this->ticketRepository->getAllTicketsCoro(outputJson);
            auto response = HttpResponse::newHttpJsonResponse(outputJson);
            response->setStatusCode(k200OK);
            callback(response);
        }
        catch (const std::exception&e){
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k500InternalServerError);
            std::cerr << "Error:" << e.what() << std::endl;
            resp->setBody(e.what());
            callback(resp);

        }
    co_return;
}

auto TicketController::createTicket(HttpRequestPtr req, std::function<void(
        const drogon::HttpResponsePtr &)> callback) -> drogon::Task<> {
    try{
        if(req == nullptr){
            throw std::exception();
        }

        auto reqBody = *(req->getJsonObject());
        Ticket ticket = Ticket::fromJson(reqBody);
        auto result = co_await this->ticketRepository->createTicketCoro(ticket);
        auto response = HttpResponse::newHttpJsonResponse(result.body.value());
        response->setStatusCode(result.responseCode);
        callback(response);
    }
    catch (const std::exception &e){
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        std::cerr << "Error:" << e.what() << std::endl;
        resp->setBody(e.what());
        callback(resp);
    }
    co_return;
}

auto TicketController::updateTicket(HttpRequestPtr req, std::function<void(const drogon::HttpResponsePtr &)> callback,
                                    std::string ticket_id) -> drogon::Task<> {
    try{
        if(req == nullptr){
            throw std::exception();
        }
        int id_int = std::stoi(ticket_id);
        auto reqBody = *(req->getJsonObject());
        Ticket ticket = Ticket::fromJson(reqBody);
        auto result = co_await this->ticketRepository->updateTicketCoro(id_int,reqBody);
        auto response = HttpResponse::newHttpJsonResponse(result.body.value());
        response->setStatusCode(result.responseCode);
        callback(response);
    }
    catch (const std::exception &e){
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        std::cerr << "Error:" << e.what() << std::endl;
        resp->setBody(e.what());
        callback(resp);
    }
    co_return;
}

auto TicketController::getOpenTickets(HttpRequestPtr req,
                                     std::function<void(const drogon::HttpResponsePtr &)> callback) -> drogon::Task<> {
    try{
        Json::Value out;
        auto result = co_await this->ticketRepository->getOpenTickets(out);
        auto response = HttpResponse::newHttpJsonResponse(out);
        response->setStatusCode(k200OK);
        callback(response);
    }
    catch (const std::exception &e){
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        std::cerr << "Error:" << e.what() << std::endl;
        resp->setBody(e.what());
        callback(resp);
    }
    co_return;
}

auto TicketController::getTicketsByUser(HttpRequestPtr req, std::function<void(
        const drogon::HttpResponsePtr &)> callback,std::string user_id) -> drogon::Task<> {
    try{
        Json::Value out;
        int user_id_integer = std::stoi(user_id);
        auto result = co_await this->ticketRepository->getTicketsByUserCoro(user_id_integer,out);
        auto response = HttpResponse::newHttpJsonResponse(out);
        response->setStatusCode(k200OK);
        callback(response);
    }
    catch (const std::exception &e){
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        std::cerr << "Error:" << e.what() << std::endl;
        resp->setBody(e.what());
        callback(resp);
    }
    co_return;
}

auto TicketController::assignTicket(HttpRequestPtr req,
                                    std::function<void(const drogon::HttpResponsePtr &)> callback,std::string ticket_id,std::string user_id) -> drogon::Task<> {
    try{
        Json::Value out;
        int ticket_id_integer = std::stoi(ticket_id);
        int user_id_integer = std::stoi(user_id);
        auto result = co_await this->ticketRepository->getTicketByIdCoro(ticket_id_integer,out);

        if(result.has_value()){
            Ticket fetchedTicket = result.value();
            fetchedTicket.setIdPessoa(user_id_integer);
            fetchedTicket.setStatus(Status::InProgress);
            out = std::move(fetchedTicket.toJson(fetchedTicket));

            auto resultUpdate = co_await this->ticketRepository->updateTicketCoro(ticket_id_integer,out);
            auto response = HttpResponse::newHttpJsonResponse(resultUpdate.body.value());
            std::cout << resultUpdate.body.value() << std::endl;

            response->setStatusCode(k200OK);
            callback(response);
        }
        auto response = HttpResponse::newHttpResponse();
        response->setStatusCode(k204NoContent);
        callback(response);
        co_return;
    }
    catch (const std::exception &e){
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        std::cerr << "Error:" << e.what() << std::endl;
        resp->setBody(e.what());
        callback(resp);
    }
    co_return;
}


auto TicketController::completeTicket(HttpRequestPtr req,
                                      std::function<void(const drogon::HttpResponsePtr &)> callback,std::string ticket_id) -> drogon::Task<> {
    try{
        Json::Value out;
        int ticket_id_integer = std::stoi(ticket_id);
        auto result = co_await this->ticketRepository->getTicketByIdCoro(ticket_id_integer,out);

        if(result.has_value()){
            Ticket fetchedTicket = result.value();
            fetchedTicket.setStatus(Status::Resolved);
            out = std::move(fetchedTicket.toJson(fetchedTicket));
            auto resultUpdate = co_await this->ticketRepository->updateTicketCoro(ticket_id_integer,out);
            auto response = HttpResponse::newHttpJsonResponse(resultUpdate.body.value());
            std::cout << resultUpdate.body.value() << std::endl;

            response->setStatusCode(k200OK);
            callback(response);
        }
        auto response = HttpResponse::newHttpResponse();
        response->setStatusCode(k204NoContent);
        callback(response);
        co_return;
    }
    catch (const std::exception &e){
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        std::cerr << "Error:" << e.what() << std::endl;
        resp->setBody(e.what());
        callback(resp);
    }
    co_return;
}
