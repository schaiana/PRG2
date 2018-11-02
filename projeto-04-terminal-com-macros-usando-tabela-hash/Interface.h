/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interface.h
 * Author: schaiana
 *
 * Created on 4 de Abril de 2016, 20:56
 */

#ifndef INTERFACE_H
#define INTERFACE_H
#include "shell.h"
#include "Historico.h"
#include "Macros.h"
#include "Variaveis.h"

class Interface {
    
public:
    void serveComandos();
    Interface();
    virtual ~Interface();
    
    Variaveis* vars;
    Macros* macros;
    Historico* historico;
private:
    Shell cmd; //executor de comandos
    string comando, prompt, comandoExit;    //comando a ser executado, prompt de espera, saída
    int resultado; //se voltar zero, não teve erros
    
    void executaComando(string comando);
    void analisaDefMacro(string nome, string comando);
    void removeEspacoAntes(string &str);
    void removeEspacoDepois(string &str);
    void substituiVar(string &str);
};

#endif /* INTERFACE_H */

