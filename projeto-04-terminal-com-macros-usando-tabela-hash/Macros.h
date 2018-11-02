/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Macros.h
 * Author: schaiana
 *
 * Created on 24 de Abril de 2016, 23:18
 */

#ifndef MACROS_H
#define MACROS_H

#include <iostream>
#include "Fila.h"
#include "Hash.h"

using namespace std;


class Macros {
public:
    Macros();
    Macros(const Macros& orig);
    virtual ~Macros();
    
    void adicionaMacro(string nome, Fila<string> comandos); // adiciona a macro ao vetor de macros
    bool existeMacro(string nome); // retorna 1 se a macro com o nome "nome" existir ou 0 se não existir
    Fila<string> retornaComandosMacro(string nome); // retorna uma fila com os comandos da macro "nome"
private:
    void configuraMacros();
    
    TabelaHash<Fila<string> > * HashMacros; // tabela hash que armazena as macros
    int capacidadeMacros;
};

#endif /* MACROS_H */

