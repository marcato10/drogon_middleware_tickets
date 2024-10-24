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
            for(auto& row: outputJson){
                std::cout<< row << std::endl;
            }
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

auto TicketController::getOpenTicket(HttpRequestPtr req,
                                     std::function<void(const drogon::HttpResponsePtr &)> callback) -> drogon::Task<> {
    return nullptr;
}

auto TicketController::getTicketByUser(HttpRequestPtr req, std::function<void(
        const drogon::HttpResponsePtr &)> callback) -> drogon::Task<> {
    return nullptr;
}
