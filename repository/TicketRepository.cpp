//
// Created by marcato on 24/10/24.
//

#include "TicketRepository.hpp"


drogon::Task<std::vector<Ticket>> Middleware::TicketRepository::getAllTicketsCoro(Json::Value& out) {
    auto request = co_await this->proxyClient->getCoro("/tickets");
    std::vector<Ticket>ticketsResponse;
    if(request.body.has_value()){
        out = std::move(request.body.value());
    }
    co_return ticketsResponse;
}

drogon::Task<Middleware::ServerResponse> Middleware::TicketRepository::createTicketCoro(Ticket ticket) {
    Json::Value jbody = ticket.toJson(ticket);
    auto request = co_await this->proxyClient->postCoro("/tickets",jbody);
    co_return request;
}

drogon::Task<Middleware::ServerResponse>
Middleware::TicketRepository::updateTicketCoro(int ticket_id, Json::Value &input) {
    auto proxyResponse = co_await this->proxyClient->putCoro("/tickets/"+std::to_string(ticket_id),input);
    co_return proxyResponse;
}

drogon::Task<std::vector<Ticket>> Middleware::TicketRepository::getTicketsByUserCoro(int user_id,Json::Value& out) {
    auto proxyResponse = co_await this->proxyClient->getCoro("/tickets/usuario/"+std::to_string(user_id));
    std::vector<Ticket>ticketsResponse;
    if(proxyResponse.body.has_value()){
        out = std::move(proxyResponse.body.value());
    }
    co_return ticketsResponse;
}


drogon::Task<std::vector<Ticket>> Middleware::TicketRepository::getOpenTickets(Json::Value &out) {
    auto proxyResponse = co_await this->proxyClient->getCoro("/tickets/abertos");
    std::vector<Ticket>ticketsResponse;
    if(proxyResponse.body.has_value()){
        out = std::move(proxyResponse.body.value());
    }
    co_return ticketsResponse;
}

drogon::Task<std::vector<Ticket>> Middleware::TicketRepository::getInProgressTicketsCoro(Json::Value &out) {
    auto proxyResponse = co_await this->proxyClient->getCoro("/tickets/andamento");
    std::vector<Ticket>ticketsResponse;
    if(proxyResponse.body.has_value()){
        out = std::move(proxyResponse.body.value());
    }
    co_return ticketsResponse;
}

drogon::Task<std::vector<Ticket>> Middleware::TicketRepository::getCompletedTicketsCoro(Json::Value& out) {
    auto proxyResponse = co_await this->proxyClient->getCoro("/tickets/completos");
    std::vector<Ticket>ticketsResponse;
    if(proxyResponse.body.has_value()){
        out = std::move(proxyResponse.body.value());
    }
    co_return ticketsResponse;
}

drogon::Task<std::optional<Ticket>> Middleware::TicketRepository::getTicketByIdCoro(int ticket_id, Json::Value &out) {
    auto request = co_await this->proxyClient->getCoro("/tickets/"+std::to_string(ticket_id));
    if(request.body.has_value()){
        Ticket ticket = Ticket::fromJson(request.body.value());
        out = std::move(request.body.value());
        co_return ticket;
    }
    co_return std::nullopt;
}
