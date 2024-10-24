#ifndef MIDDLEWARE_PERSON_HPP
#define MIDDLEWARE_PERSON_HPP
#include <iostream>
#include <utility>
#include <optional>
#include <drogon/drogon.h>
struct Login {
    std::string login;
    explicit Login(std::string login) : login(std::move(login)){};
};

struct Senha {
    std::string senha;
    explicit Senha(std::string senha) : senha(std::move(senha)){};
};

struct PessoaDAO {
    Login login;
    Senha senha;

    explicit PessoaDAO(Login login, Senha senha)
            : login(std::move(login)), senha(std::move(senha)){};
};

class Pessoa {
private:
    std::optional<int> id;
    Login login;
    Senha senha;
    bool adm;

public:

    explicit Pessoa(const int &id, Login l, Senha senha,
                    const bool &adm)
            : id(id), login(std::move(l)), senha(std::move(senha)), adm(adm){};
    explicit Pessoa(Login l, Senha senha,
                    const bool &adm)
            : id(std::nullopt), login(std::move(l)), senha(std::move(senha)), adm(adm){};
    Json::Value toJson(const Pessoa& pessoa);
    static Pessoa fromJson(const Json::Value& jsonPessoa);
    ~Pessoa() = default;
    std::optional<int> getPessoaId();
    void setPessoaId(int personId);
    const Login& getLogin();
    const Senha& getSenha();
    bool isAdm() const;

};
#endif //MIDDLEWARE_PERSON_HPP
