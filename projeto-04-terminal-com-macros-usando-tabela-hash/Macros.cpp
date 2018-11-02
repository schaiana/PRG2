/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Macros.cpp
 * Author: schaiana
 * 
 * Created on 24 de Abril de 2016, 23:18
 */

#include "Macros.h"

Macros::Macros() {
    capacidadeMacros = 50;
    HashMacros = new TabelaHash<Fila<string> >(capacidadeMacros);
    
    configuraMacros(); //adiciona macros pré definidas na tabela hash
}

Macros::Macros(const Macros& orig) {
}

Macros::~Macros() {
    delete HashMacros;
}

void Macros::adicionaMacro(string nome, Fila<string> comandos) {
    //se a tabela hash não estiver cheia, adiciona a macro
    if (HashMacros->tamanho() <= capacidadeMacros) {
        HashMacros->adiciona(nome, comandos);
    }
}

void Macros::configuraMacros() {
    Fila<string> comandosMacro1; // cria uma nova fila de comandos para a macro
    comandosMacro1.enfileira("ls"); // adiciona o comando para a fila da macro
    comandosMacro1.enfileira("date"); // adiciona o comando para a fila da macro
    adicionaMacro("macro1", comandosMacro1); // adiciona a macro
    
    
    Fila<string> comandosMacro2; // cria uma nova fila de comandos para a macro
    comandosMacro2.enfileira("macro1"); // adiciona o comando macro1 nesta macro
    adicionaMacro("macro2", comandosMacro2);// adiciona a macro
}

// retorna 1 se a macro com o nome "nome" existir ou 0 se não existir
bool Macros::existeMacro(string nome) {
    return HashMacros->existe(nome);
}

Fila<string> Macros::retornaComandosMacro(string nome) {
    return HashMacros->obtem(nome); //retorna valor da chave "nome" da tabela hash    
}
