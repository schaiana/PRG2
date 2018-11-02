/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interface.cpp
 * Author: schaiana
 * 
 * Created on 4 de Abril de 2016, 20:56
 */

#include "Interface.h"
#include "shell.h"
#include <iostream>
#include <cstdlib>


Interface::Interface() {
    historico = new Historico(20);
    macros = new Macros();
    prompt = "=>";
    comandoExit = "sair";
    
}


Interface::~Interface() {
}

void Interface::serveComandos() {    
    while(1){
        cout << prompt;
        getline(cin, comando);
        int pos = comando.find(' ');
        string entrada = comando.substr(0, pos);
        string nomevar = comando.substr(pos+1, '=');
        if (entrada == "defvar"){
        cout << "entrada foi defvar" << endl;
        cout << "O nome da variável é: " << nomevar << endl;
        }
        string comandosalvo = comando.substr('=', );
    
        executaComando(comando);
    }
}

void Interface::variavel() {
    
    
}

void Interface::executaComando(string comando) {
    if (comando == comandoExit){
        exit(0);           
    } else if(comando == "historico"){ // se o comando executado foi "historico"
        historico->adiciona(comando); // adiciona o comando "historico" ao historico
        historico->mostrarHistorico(); // mostra o historico de comandos executados
    } else if(comando.substr(0,1)=="!"){ // verifica se o primeiro caractere do comando é "!"
        int nComando = atoi(comando.substr(1, comando.size()).c_str()); // converte para int oque foi escrito depois do "!"
        string comandoHistorico = historico->getComandoN(nComando); // busca pelo comando N no historico
        if(comandoHistorico==""){ // caso o comando N não exista no historico
            cout << "historico !" << nComando << " nao existe" << endl;
        } else { // caso contrario executa o comando
            cout << comandoHistorico << endl;
            executaComando(comandoHistorico);
        }
    } else if(macros->existeMacro(comando)){ // existe uma macro com o nome "comando"
        historico->adiciona(comando); // adiciona a macro no historico
        Fila<string> comandosMacro(macros->retornaComandosMacro(comando)); // cria uma fila com os comandos da macro
        while(!comandosMacro.vazia()){ // executa o while enquanto a fila não estiver vazia
            string proximoComando = comandosMacro.desenfileira(); // retorna um item da fila
            cout << proximoComando << endl;
            executaComando(proximoComando); // executa o comando da fila
        }
    } else { // executa o comando na classe shell
        historico->adiciona(comando); // adiciona o comando ao historico
        resultado = cmd.execute(comando);
        cout << "Status: " << resultado << endl;
    }
}
