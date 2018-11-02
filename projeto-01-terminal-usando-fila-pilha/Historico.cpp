/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Historico.cpp
 * Author: schaiana
 * 
 * Created on 23 de Abril de 2016, 21:37
 */

#include "Historico.h"
#include "Pilha.h"
#include <iostream>

using namespace std;

Historico::Historico(int capacidade) {
    capacidadeHistorico = capacidade;
    pilhaHistorico = new Pilha<string>(capacidadeHistorico);
}

Historico::Historico(const Historico& orig) {
}

Historico::~Historico() {
}

void Historico::adiciona(string comando){
    if(!pilhaHistorico->cheia()){
        pilhaHistorico->push(comando);
    }
}

void Historico::mostrarHistorico() {
    cout << "=== Historico de comandos ===" << endl ;
    
    if(pilhaHistorico->vazia()){
        cout << "Historico vazio"<<endl;
    } else {
        Pilha<string> pilhaTemp(*pilhaHistorico);
        Pilha<string> pilhaTemp2(capacidadeHistorico);
        
        while(!pilhaTemp.vazia()){
            pilhaTemp2.push(pilhaTemp.pop());
            //cout << pilhaTemp.pop() << endl;
        }
        
        while(!pilhaTemp2.vazia()){
            cout << pilhaTemp2.pop() << endl;
        }
        
    }
}

// retorna o comando N ou retorna "" caso comando N não estaja no historico
string Historico::getComandoN(int n) {
    string comandoN = "";
    
    if(!pilhaHistorico->vazia() && n>0){
        Pilha<string> pilhaTemp(*pilhaHistorico);
        for(int i = 1; i<=n; i++){
            if(pilhaTemp.vazia()){
                break;
            }
            if(i==n){
                comandoN = pilhaTemp.pop();
                break;
            } else {
                pilhaTemp.pop();
            }
        }
    }
    
    return comandoN;
}
