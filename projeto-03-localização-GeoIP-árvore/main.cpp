/* 
 * File:   main.cpp
 * Author: msobral
 *
 * Created on 1 de Abril de 2016, 14:04
 */

#include <iostream>
#include <unistd.h>
#include "string.h"
#include <cstdlib>
#include <stdio.h>
#include "GeoIP.h"
#include "Lista.h"
#include <fstream>
#include <errno.h>
#include <sstream>
#include "Arvore.h"
#include <fstream>
#include <errno.h>
#include "Interface.h"
#include <locale.h>

using namespace std;



int main(int argc, char** argv) {
    Interface minhaInterface;

    while(1){
        minhaInterface.mostraMenu();
    }
    
    return 0;
}
