/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: schaiana
 *
 * Created on 4 de Abril de 2016, 20:06
 */

#include <cstdlib>
#include <iostream>
#include "Interface.h"
#include "Hash.h"
#include <string>

using namespace std;

/*
 * 
 */
int main(){

    Interface minhainterface; //minhainterface é um objeto da classe Interface (representação da classe)
    minhainterface.serveComandos(); //serveComandos é um método da classe Interface (é uma característica, o jeito que a classe opera)     

/*

  TabelaHash<int> tab1(5);
  string chaves[8] = {"chave1", "chave2", "chave3", "chave4", "chave5", "chave6", "chave7", "chave8"};
  int dados[8] = {11, 12, 13 , 14, 15, 16, 17, 18};
 
  for (int n=0; n < 8; n++) {
    tab1.adiciona(chaves[n], dados[n]);
  }
  
 
  for (int n=0; n < 8; n++) {
   cout << "tab1[" << chaves[n] << "] = " << tab1[chaves[n]] << endl;
  }
  
  Lista<string> * lchaves = tab1.chaves();
  Lista<int> * lvalores = tab1.valores();
  lchaves->escrevaSe(cout);
  lvalores->escrevaSe(cout);
  
  
  */
  return 0;    
}

    


//ao criar o objeto minhainterface, o construtor da classe Interface é chamado.