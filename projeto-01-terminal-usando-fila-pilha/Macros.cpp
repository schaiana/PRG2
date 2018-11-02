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
    nMacros = 0;
    vetorMacros = new macro[capacidadeMacros];
    
    configuraMacros();
}

Macros::Macros(const Macros& orig) {
}

Macros::~Macros() {
}

void Macros::adicionaMacro(string nome, Fila<string> comandos) {
    if(nMacros<=capacidadeMacros){
        vetorMacros[nMacros].nome = nome;
        vetorMacros[nMacros].comandos = new Fila<string>(comandos);
        nMacros++;
    }
}

void Macros::configuraMacros() {
    Fila<string> comandosMacro1(2); // cria uma nova fila de comandos para a macro
    comandosMacro1.enfileira("ls"); // adiciona o comando para a fila da macro
    comandosMacro1.enfileira("date"); // adiciona o comando para a fila da macro
    adicionaMacro("macro1", comandosMacro1); // adiciona a macro
    
    
    Fila<string> comandosMacro2(1); // cria uma nova fila de comandos para a macro
    comandosMacro2.enfileira("macro1"); // adiciona o comando macro1 nesta macro
    adicionaMacro("macro2", comandosMacro2);// adiciona a macro
}

// retorna 1 se a macro com o nome "nome" existir ou 0 se não existir
bool Macros::existeMacro(string nome) {
    for(int i=0; i<nMacros; i++){
        if(vetorMacros[i].nome==nome){
            return 1;
        }
    }
    return 0;
}

Fila<string> Macros::retornaComandosMacro(string nome) {
    for(int i=0; i<nMacros; i++){
        if(vetorMacros[i].nome==nome){
            return *(vetorMacros[i].comandos);
        }
    }
}
