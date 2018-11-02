/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Variaveis.h
 * Author: schaiana
 *
 * Created on 25 de Julho de 2016, 22:45
 */

#ifndef VARIAVEIS_H
#define VARIAVEIS_H
#include <iostream>
#include "Hash.h"

using namespace std;

class Variaveis {
public:
    Variaveis();
    Variaveis(const Variaveis& orig);
    virtual ~Variaveis();
    void adicionaVar(string nome, string valor); // adiciona a variável
    string retornaValorVar(string & nome);
    bool existeVar(string nome); // retorna 1 se a variável com o nome "nome" existir ou 0 se não existir
private:
    int capacidadeVar;
    TabelaHash<string> * HashVar; // tabela hash que armazena as variáveis

};

#endif /* VARIAVEIS_H */

