//
// Created by marcato on 24/10/24.
//

#ifndef MIDDLEWARE_TICKETCONTROLLER_HPP
#define MIDDLEWARE_TICKETCONTROLLER_HPP
#include <drogon/drogon.h>
#include "TicketRepository.hpp"
#include <drogon/utils/coroutine.h>
namespace ticket{
    class TicketController : public drogon::HttpController<TicketController,false>{
    private:
        std::shared_ptr<Middleware::TicketRepository>ticketRepository;

    public:
        explicit TicketController(std::shared_ptr<Middleware::TicketRepository> tickRep) : ticketRepository(std::move(tickRep)){};
        TicketController() : ticketRepository(std::make_shared<Middleware::TicketRepository>()){};
        auto getAllTickets(HttpRequestPtr req,std::function<void(const drogon::HttpResponsePtr&)> callback)->drogon::Task<>;
        auto createTicket(HttpRequestPtr req,std::function<void(const drogon::HttpResponsePtr&)> callback)->drogon::Task<>;

        auto getOpenTickets(HttpRequestPtr req,std::function<void(const drogon::HttpResponsePtr&)> callback)->drogon::Task<>;
        auto updateTicket(HttpRequestPtr req,std::function<void(const drogon::HttpResponsePtr&)> callback,std::string ticket_id)->drogon::Task<>;
        auto getTicketsByUser(HttpRequestPtr req,std::function<void(const drogon::HttpResponsePtr&)> callback,std::string user_id)->drogon::Task<>;
        auto completeTicket(HttpRequestPtr req,std::function<void(const drogon::HttpResponsePtr&)> callback,std::string ticket_id)->drogon::Task<>;
        auto assignTicket(HttpRequestPtr req,std::function<void(const drogon::HttpResponsePtr&)> callback,std::string ticket_id,std::string user_id)->drogon::Task<>;

        METHOD_LIST_BEGIN
            ADD_METHOD_TO(TicketController::getAllTickets,"/tickets",HttpMethod::Get);
            ADD_METHOD_TO(TicketController::createTicket, "/tickets", HttpMethod::Post);
            ADD_METHOD_TO(TicketController::getOpenTickets, "/tickets/open", HttpMethod::Get);
            ADD_METHOD_TO(TicketController::getTicketsByUser, "/tickets/usuario/{user_id}", HttpMethod::Get);
            ADD_METHOD_TO(TicketController::completeTicket, "/tickets/{ticket_id}/complete", HttpMethod::Put);
            ADD_METHOD_TO(TicketController::assignTicket, "/tickets/{ticket_id}/assign/{user_id}", HttpMethod::Put);
        METHOD_LIST_END


    };

};

#endif //MIDDLEWARE_TICKETCONTROLLER_HPP
