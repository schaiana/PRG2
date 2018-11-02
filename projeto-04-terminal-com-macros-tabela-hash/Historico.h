/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Historico.h
 * Author: schaiana
 *
 * Created on 23 de Abril de 2016, 21:37
 */

#ifndef HISTORICO_H
#define HISTORICO_H

#include <iostream>

#include "Pilha.h"



using namespace std;

class Historico {
public:
    Historico(int capacidade);
    Historico(const Historico& orig);
    virtual ~Historico();
    
    void adiciona(string comando); // adiciona comando ao historico
    void mostrarHistorico(); // mostra os comandos do historico
    string getComandoN(int n); //retorna o comando "n" do historico
private:
    Pilha<string>* pilhaHistorico; // pilha que armazena os comandos do historico
    int capacidadeHistorico;
};

#endif /* HISTORICO_H */

