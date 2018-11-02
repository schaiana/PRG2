#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <limits>
#include <time.h>
#include "Arvore.h"
#include "GeoIP.h"
#include "BaseGeoIP.h"

using namespace std;

class Interface {
public:
    Interface();
    Interface(const Interface& orig);
    virtual ~Interface();
    
    void mostraMenu();
private:
    string linha;
    void mostraMenu2(string arqbloc, string arqloc, bool embaralhar);
};

#endif /* INTERFACE_H */

