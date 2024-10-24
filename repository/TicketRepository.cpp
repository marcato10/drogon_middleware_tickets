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

drogon::Task<std::vector<Ticket>> Middleware::TicketRepository::getTicketsByUserCoro(int user_id) {
    return nullptr;
}

/*
drogon::Task<Middleware::ServerResponse> Middleware::TicketRepository::createTicket(const Ticket &ticket) {
    return nullptr;
}

drogon::Task<Middleware::ServerResponse>
Middleware::TicketRepository::updateTicket(int ticket_id, const Ticket &ticket) {
    return nullptr;
}

drogon::Task<std::vector<Ticket>> Middleware::TicketRepository::getCompletedTickets() {
    return nullptr;
}

drogon::Task<std::vector<Ticket>> Middleware::TicketRepository::getIncompleteTickets() {
    return nullptr;
}

drogon::Task<std::vector<Ticket>> Middleware::TicketRepository::getTicketsByUser(int user_id) {
    return nullptr;
}

drogon::Task<std::optional<Ticket>> Middleware::TicketRepository::getTicketById(int ticket_id) {
    return nullptr;
}
*/