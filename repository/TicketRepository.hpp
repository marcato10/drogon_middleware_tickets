#ifndef MIDDLEWARE_TICKETREPOSITORY_HPP
#define MIDDLEWARE_TICKETREPOSITORY_HPP
#include <iostream>
#include <string>
#include <vector>
#include "ticket.hpp"
#include "proxy_client.hpp"

namespace Middleware {
    class TicketRepository {
    private:
    std::shared_ptr<Middleware::ProxyClient>proxyClient;
    public:
        TicketRepository() : proxyClient(std::make_shared<ProxyClient>()) {}
        explicit TicketRepository(const std::shared_ptr<ProxyClient>&proxy) : proxyClient(proxy) {}

        drogon::Task<std::vector<Ticket>> getAllTicketsCoro(Json::Value& out);
        drogon::Task<ServerResponse> createTicketCoro(Ticket ticket);
        drogon::Task<ServerResponse> updateTicketCoro(int ticket_id, Json::Value& input);
        drogon::Task<std::vector<Ticket>> getCompletedTicketsCoro(Json::Value& out);
        drogon::Task<std::vector<Ticket>> getInProgressTicketsCoro(Json::Value& out);
        drogon::Task<std::vector<Ticket>> getOpenTickets(Json::Value& out);
        drogon::Task<std::vector<Ticket>> getTicketsByUserCoro(int user_id,Json::Value& out);
        drogon::Task<std::optional<Ticket>> getTicketByIdCoro(int ticket_id,Json::Value& out);
    };
};

#endif //MIDDLEWARE_TICKETREPOSITORY_HPP
