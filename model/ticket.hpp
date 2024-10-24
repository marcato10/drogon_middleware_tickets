#ifndef MIDDLEWARE_TICKET_HPP
#define MIDDLEWARE_TICKET_HPP
#include <optional>
#include <vector>
#include <string>
#include <drogon/drogon.h>

enum class Status : int { Pending = 0, InProgress = 1, Resolved = 2 };

struct Titulo{
    std::string titulo;
    explicit Titulo(std::string titulo_) : titulo(std::move(titulo_)){};
};
struct Descricao{
    std::string descricao;
    explicit Descricao(std::string descricao_) : descricao(std::move(descricao_)) {};
};

class Ticket {
private:
  std::optional<int> id;
  Titulo titulo;
  Descricao descricao;
  int prioridade;
  std::optional<int> id_pessoa;
  Status status;

public:
    //Default Constructor
    explicit Ticket(int id_,Titulo titulo_, Descricao descricao_,int prioridade_,int id_pessoa_,Status status_)
            : id(id_), titulo(std::move(titulo_)), descricao(std::move(descricao_)),prioridade(prioridade_),id_pessoa(id_pessoa_),status(status_) {};

    explicit Ticket(Titulo titulo_, Descricao descricao_,int prioridade_,Status status_)
    : id(0), titulo(std::move(titulo_)), descricao(std::move(descricao_)),prioridade(prioridade_),id_pessoa(std::nullopt),status(status_) {};
    ~Ticket() = default;

    Json::Value toJson(const Ticket& ticket);
    static Ticket fromJson(const Json::Value& jsonTicket);

    std::optional<int> getId();
    const std::string &getTitulo();
    const std::string &getDescricao();
    int getPrioridade() const;
    std::optional<int> getIdPessoa();
    Status getStatus() const;
    int getStatusInt() const;

};
#endif