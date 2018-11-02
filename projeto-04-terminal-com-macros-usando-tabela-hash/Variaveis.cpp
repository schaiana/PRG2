/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Variaveis.cpp
 * Author: schaiana
 * 
 * Created on 25 de Julho de 2016, 22:45
 */

#include "Variaveis.h"


Variaveis::Variaveis() {
    capacidadeVar = 100;
    HashVar = new TabelaHash<string>(capacidadeVar);
}

Variaveis::Variaveis(const Variaveis& orig) {
}

Variaveis::~Variaveis() {
    delete HashVar;
}

void Variaveis::adicionaVar(string nome, string valor) {
    //se a tabela hash não estiver cheia, adiciona a variável
    if (HashVar->tamanho() <= capacidadeVar) {
        HashVar->adiciona(nome, valor);
    }
}    

bool Variaveis::existeVar(string nome) {
    return HashVar->existe(nome);
}

string Variaveis::retornaValorVar(string & nome) {
    return HashVar->obtem(nome);
}