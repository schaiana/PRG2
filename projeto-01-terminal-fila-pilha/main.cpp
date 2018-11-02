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

using namespace std;

/*
 * 
 */
int main(){

    Interface minhainterface; //minhainterface é um objeto da classe Interface (representação da classe)
    minhainterface.serveComandos(); //serveComandos é um método da classe Interface (é uma característica, o jeito que a classe opera)     

    return 0;    
    
}

//ao criar o objeto minhainterface, o construtor da classe Interface é chamado.