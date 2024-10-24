//
// Created by marcato on 19/10/24.
//

#include "person.hpp"

std::optional<int> Pessoa::getPessoaId() {
    return this->id;
}

void Pessoa::setPessoaId(int personId) {
    this->id = personId;
}

const Login &Pessoa::getLogin() {
    return this->login;
}

const Senha &Pessoa::getSenha() {
    return this->senha;
}

bool Pessoa::isAdm() const {
    return this->adm;
}

Json::Value Pessoa::toJson(const Pessoa &pessoa) {
    Json::Value jsonPessoa;
    if(pessoa.id.has_value()){
        jsonPessoa["ID"] = pessoa.id.value();
    }

    jsonPessoa["Login"] = pessoa.login.login;
    jsonPessoa["Senha"] = pessoa.senha.senha;
    jsonPessoa["ADM"] = pessoa.adm;
    return jsonPessoa;
}

Pessoa Pessoa::fromJson(const Json::Value &jsonPessoa) {
    if(jsonPessoa.isMember("ID")){
        return Pessoa(jsonPessoa["ID"].asInt(),Login(jsonPessoa["Login"].asString()), Senha(jsonPessoa["Senha"].asString()), jsonPessoa["ADM"].asBool());
    }
    std::cout << "Entrou no fromJson" << std::endl;
    return Pessoa(Login(jsonPessoa["Login"].asString()), Senha(jsonPessoa["Senha"].asString()), false);
}


