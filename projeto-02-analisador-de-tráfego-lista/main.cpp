/* 
 * File:   main.cpp
 * Author: msobral
 *
 * Created on 1 de Abril de 2016, 14:04
 * 
 * 
 * IMPORTANTE: INCLUIR "-std=c++11" NAS OPÇÕES DE COMPILAÇÃO PARA O "to_string()" FUNCIONAR
 * 
 */

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "Capturador.h"
#include "Interface.h"

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {
    Interface minhaInterface;

    while(1){
        minhaInterface.mostraMenu();
    }
  
    return 0;
}

