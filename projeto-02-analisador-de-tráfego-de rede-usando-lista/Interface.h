/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interface.h
 * Author: schaiana
 *
 * Created on 29 de Maio de 2016, 15:43
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <limits>
#include <time.h>
#include "Analisador.h"
#include "Lista.h"

using namespace std;

class Interface {
public:
    Interface();
    Interface(const Interface& orig);
    virtual ~Interface();
    
    void mostraMenu();
private:
    Analisador meuAnalisador;
    int npacotes;
    int tempo;
    Lista<Frame>* listaPacotes;
    float tempoDuracaoCaptura;
    
    void mostraMenu2(bool ehInterface);
    void pausa();
    double taxaCaptura;
};

#endif /* INTERFACE_H */

