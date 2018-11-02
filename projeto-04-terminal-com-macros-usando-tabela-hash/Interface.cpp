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
    vars = new Variaveis();
    prompt = "=>";
    comandoExit = "sair";
    
}


Interface::~Interface() {
    delete historico;
    delete macros;
    delete vars;
}

void Interface::serveComandos() {    
    while(1){
        cout << prompt;
        getline(cin, comando);
        int pos = comando.find(' ');
        string entrada = comando.substr(0, pos);
        if (entrada == "defvar" || entrada == "defmacro"){ //se o comando digitado pelo usuário é defmacro ou defvar
            int pos2 = comando.find('=');
            string nomeVar = comando.substr(pos+1, pos2 - (pos+1)); //nome da variável ou macro
            string comandoSalvo = comando.substr(pos2 + 1, string::npos); //comandos da macro ou conteúdo da variável (ex: um caminho)
            if (entrada == "defvar") {
                removeEspacoAntes(nomeVar);
                removeEspacoDepois(nomeVar);
                vars->adicionaVar(nomeVar, comandoSalvo);
            } else if (entrada == "defmacro") {
                analisaDefMacro(nomeVar, comandoSalvo);
            }
        } else {
            executaComando(comando);
        }
        
    }
}

void Interface::analisaDefMacro(string nome, string comando) {
    int pos = 0;
    int tamanho;
    Fila<string> comandosMacro;
    while (comando.find(';', pos) != string::npos) { //enquando achar um ;, executa o while
        tamanho = comando.find(';', pos) - pos; //começa procurando do pos+1 e vai até achar o ;
        string cmdMacro = comando.substr(pos, tamanho);
        removeEspacoAntes(cmdMacro);
        removeEspacoDepois(cmdMacro);
        comandosMacro.enfileira(cmdMacro);
        pos += tamanho + 1; //pos = pos + tamanho = 1
    }
    string comandoFinal = comando.substr(pos, string::npos);
    removeEspacoAntes(comandoFinal);
    removeEspacoDepois(comandoFinal);
    if (!comandoFinal.empty()) {
        comandosMacro.enfileira(comandoFinal);
    }
    removeEspacoAntes(nome);
    removeEspacoDepois(nome);
    macros->adicionaMacro(nome, comandosMacro);    
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
        substituiVar(comando);
        resultado = cmd.execute(comando);
        cout << "Status: " << resultado << endl;
    }
}
void Interface::removeEspacoAntes(string &str) { //remover espaços em branco no início da string
    if (!str.empty()) { //se a string for vazia, acessará a posição 0, que é inválida, esse if previne isso
        while (str[0] == ' ') { //se o caractere da posição 0 for igual a um espaço, será removido
            str.erase(0,1);
            if (str.empty()) {
                break;
            }
        }
    }
}

void Interface::removeEspacoDepois(string &str) {
    if (!str.empty()) { //se a string for vazia, acessará a posição -1, que é inválida, esse if previne isso
        while (str[str.length() - 1] == ' ') { //se o último caractere for igual a um espaço, será removido
            str.erase(str.length() - 1,1);
            if (str.empty()) {
                break;
            }
        }
    
    }
}

// substitui as variáveis pelos seus respectivos valores
void Interface::substituiVar(string &str) {
    int aPartirDe = 0; // procura $ a partir dessa posição
    while(str.find('$', aPartirDe) != string::npos) { // enquanto encontrar $, executa o while
        int pos = str.find('$', aPartirDe); // armazena a posição onde o $ foi encontrado
        int tamanho = str.find(' ', pos) - pos - 1; // armazena o tamanho do nome da variável
        string nomeVar = str.substr(pos + 1, tamanho); // armazena o nome da variável encontrada
        
        if(vars->existeVar(nomeVar)) { // se a variável for válida, ou seja, estiver na tabela
            string valorVar = vars->retornaValorVar(nomeVar);
            // substitui o nome da variável pelo seu valor
            str.replace(pos, tamanho+1, valorVar);
        } else { // se a variável não estiver na tabela
            // procura a partir do último $
            aPartirDe = pos + 1;
        }
    }
}