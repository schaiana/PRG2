#ifndef BASEGEOIP_H
#define BASEGEOIP_H


#include <limits>
#include <string>
#include <time.h>
#include "Arvore.h"
#include "GeoIP.h"
#include <fstream>
#include <errno.h>
#include "Lista.h"


using namespace std;


class BaseGeoIP {
public:
    BaseGeoIP();
    BaseGeoIP(const BaseGeoIP& orig);
    virtual ~BaseGeoIP();
    void carregaArquivoBloc(string arquivo, bool embaralhar);
    void carregaArquivoLoc(string arquivo, bool embaralhar);
    Arvore<GeoIP> * baseBloc;
    Arvore<GeoIPLocation> * baseLoc;
    void salvaArquivoBloc(string nomeArquivo);
    void salvaArquivoLoc(string nomeArquivo);
    void procuraIP(string IP, ostream & out);
    void procuraLoc(string pais, string cidade, ostream & out);
    unsigned int str2ip(const string & ip);
    string ip2str(unsigned int addr);
    void limpar();
private:

};

#endif

