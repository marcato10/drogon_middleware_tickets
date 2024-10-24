#include "ticket.hpp"

std::optional<int> Ticket::getId() {
    return this->id;
}

const std::string &Ticket::getTitulo()  {
    return this->titulo.titulo;
}

const std::string &Ticket::getDescricao()  {
    return this->descricao.descricao;
}
int Ticket::getPrioridade() const {
    return this->prioridade;
}

std::optional<int> Ticket::getIdPessoa() {
    return this->id_pessoa;
}

Status Ticket::getStatus() const {
    return this->status;
}

int Ticket::getStatusInt() const {
    return static_cast<int>(this->status);
}

Json::Value Ticket::toJson(const Ticket &ticket) {
    Json::Value jout;
    if(ticket.id.has_value()){
        jout["ID"] = ticket.id.value();
    }
    jout["Titulo"] = ticket.titulo.titulo;
    jout["Descricao"] = ticket.descricao.descricao;
    jout["Prioridade"] = ticket.prioridade;
    if(ticket.id_pessoa.has_value()){
        jout["ID_pessoa"] = ticket.id_pessoa.value();
    }
    jout["Status"] = ticket.getStatusInt();
    return jout;
}

Ticket Ticket::fromJson(const Json::Value &jsonTicket) {
    if (jsonTicket.isMember("ID") && jsonTicket.isMember("ID_pessoa")) {
        return Ticket(
                jsonTicket["ID"].asInt(),
                Titulo(jsonTicket["Titulo"].asString()),
                Descricao(jsonTicket["Descricao"].asString()),
                jsonTicket["Prioridade"].asInt(),
                jsonTicket["ID_pessoa"].asInt(),
                static_cast<Status>(jsonTicket["Status"].asInt())
        );
    }
    return Ticket(
            Titulo(jsonTicket["Titulo"].asString()),
            Descricao(jsonTicket["Descricao"].asString()),
            jsonTicket["Prioridade"].asInt(),
            static_cast<Status>(jsonTicket["Status"].asInt())
    );
}
