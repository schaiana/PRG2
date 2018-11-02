#include <unistd.h>
#include <stdlib.h>
#include "BaseGeoIP.h"

using namespace std;

BaseGeoIP::BaseGeoIP() {

}

BaseGeoIP::BaseGeoIP(const BaseGeoIP& orig) {
}

BaseGeoIP::~BaseGeoIP() {
    
}

void BaseGeoIP::carregaArquivoBloc(string arquivo, bool embaralhar){
    if (embaralhar == 1) { //quando se quer embalhar o arquivo
        cout << "Embaralhando o arquivo de blocos de IP..." << endl;
        string comandolinux = "sort -R -o arqemb.txt " + arquivo;
        system(comandolinux.c_str());
        arquivo = "arqemb.txt";
    }
    
    ifstream arq(arquivo.c_str());
    if (not arq.is_open()) {
        perror("Erro ao abrir o arquivo de blocos de IP.");
        exit(1);
    }
    
    cout << "Carregando arquivo de blocos de IP..." << endl;
    string linha;
    getline(arq, linha);
    while (!(linha[0] == '"')) {
        getline(arq, linha);
    }
    baseBloc = new Arvore<GeoIP>(GeoIP(linha));
    while (true) { 
        try {
            getline(arq, linha);
            //cout << linha << endl;
            if (arq.eof()) break;
            baseBloc->adiciona(GeoIP(linha));
        } catch (int e){
            //cerr << "Ignorando - " << e << ": " << linha << endl;
         }
    }
    cout << "Balanceando a árvore de blocos de IP..." << endl;
    baseBloc = baseBloc->balanceia();
    cout << "A altura da árvore de blocos de IP é: " << baseBloc->altura() << endl;
}

void BaseGeoIP::carregaArquivoLoc(string arquivo, bool embaralhar){
    if (embaralhar == 1) { //quando se quer embalhar o arquivo
        cout << "Embaralhando o arquivo de localidades..." << endl;
        string comandolinux = "sort -R -o arqemb2.txt " + arquivo;
        system(comandolinux.c_str());
        arquivo = "arqemb2.txt";
    }
    ifstream arq(arquivo.c_str(), ios_base::in | ios_base::binary);

    if (not arq.is_open()) {
        perror("Erro ao abrir o arquivo de localidades");
        exit(1);
    }
    cout << "Carregando arquivo de localidades..." << endl;
    string linha;
    getline(arq, linha);
    while (!(linha[0] >= '0' && linha[0] <= '9')) {
        getline(arq, linha);
    }

    baseLoc = new Arvore<GeoIPLocation>(GeoIPLocation(linha));
    while (true) { 
        try {
            getline(arq, linha);
            //cout << linha << endl;
            if (arq.eof()) break;
            baseLoc->adiciona(GeoIPLocation(linha));
        } catch (int e){
            //cerr << "Ignorando - " << e << ": " << linha << endl;
         }
    }
    cout << "Balanceando árvore de localidades..." << endl;
    baseLoc = baseLoc->balanceia();
    cout << "A altura da árvore de localidades é: " << baseLoc->altura() << endl;
}

void BaseGeoIP::salvaArquivoBloc(string nomeArquivo){
    
    ofstream arqEscrita(nomeArquivo.c_str(), ios_base::out | ios_base::trunc);
    
    if (not arqEscrita.is_open()) {
        string erro = "Erro ao salvar o arquivo: " + nomeArquivo;
        perror(erro.c_str());
        return;
    }
    baseBloc->escrevaSePreOrder(arqEscrita);
    arqEscrita.close();

}

void BaseGeoIP::salvaArquivoLoc(string nomeArquivo){
       
    ofstream arqEscrita(nomeArquivo.c_str(), ios_base::out | ios_base::trunc);
    
    if (not arqEscrita.is_open()) {
        string erro = "Erro ao salvar o arquivo: " + nomeArquivo;
        perror(erro.c_str());
        return;
    }
    baseLoc->escrevaSePreOrder(arqEscrita);
    arqEscrita.close();

}
void BaseGeoIP::limpar(){
    delete baseBloc;
    delete baseLoc;
}

void BaseGeoIP::procuraIP(string IP, ostream & out){
    unsigned int numIP;
    numIP = str2ip(IP);
    GeoIP procuraIP (numIP, numIP, 0);
    try {
        GeoIP & GeoIPBlocencontrado = baseBloc->obtem(procuraIP);
        out << "IP procurado: " << IP << endl;
        out << "O bloco de IPs associado é: " << ip2str(GeoIPBlocencontrado.get_addr1()) << " a " << ip2str(GeoIPBlocencontrado.get_addr2()) << endl;
        GeoIPLocation procuraLoc(GeoIPBlocencontrado.get_location());
        try {
            GeoIPLocation & GeoIPLocencontrado = baseLoc->obtem(procuraLoc);
             out << "A localidade associada é: " << endl << "País: " << GeoIPLocencontrado.get_pais()<< endl << "Região: " << GeoIPLocencontrado.get_regiao() << endl << "Cidade: " << GeoIPLocencontrado.get_cidade()<< endl;
             out << "Latitude: " << GeoIPLocencontrado.get_latitude() << endl << "Longitude: " << GeoIPLocencontrado.get_longitude() <<endl;
        } catch (int e) {
            out << "Não foi possível encontrar uma localidade associada. Exceção do tipo: " << e << endl;
          }
    } catch (int e) {
        out << "Não foi possível encontrar um bloco de IP associado. Exceção do tipo: " << e << endl;
    }
}

void BaseGeoIP::procuraLoc(string pais, string cidade, ostream & out) {
    bool encontrou = 0;
    Lista<GeoIPLocation> listaLoc;
    Lista<GeoIPLocation> listaLocResult;
    baseLoc->valores(listaLoc);
    listaLoc.inicia();
    while (!listaLoc.fim()){
        GeoIPLocation & temp = listaLoc.proximo();
        if ((temp.get_cidade() == cidade && temp.get_pais() == pais)
            || (temp.get_pais() == pais && cidade == "0")
            || (temp.get_cidade() == cidade && pais == "0")) {
            listaLocResult.anexa(temp);
            encontrou = 1;
        }
    }
    Lista<GeoIP> listaBloc;
    baseBloc->valores(listaBloc);
    listaLocResult.inicia();
        
    if (encontrou == 1) {
        if (cidade == "0") {
            out << "Blocos de IP associados ao país " << pais << ": " << endl; 
        } else if (pais == "0") {
            out << "Blocos de IP associados à cidade " << cidade << ": " << endl; 
          } else {
              out << "Blocos de IP associados a " << cidade  << "/" << pais << ": " << endl;   
            }
    }
    
    while (!listaLocResult.fim()) {
        GeoIPLocation & loc = listaLocResult.proximo();
        listaBloc.inicia();
        while (!listaBloc.fim()) {
            GeoIP & bloc = listaBloc.proximo();
            if (bloc.get_location() == loc.get_id()) {
                out << "Bloco de IP: " << ip2str(bloc.get_addr1()) << " a " << ip2str(bloc.get_addr2()) << endl;
            
            }
        
        }
    
    }
    
    if (encontrou == 0) {
        out << "Nenhuma localidade encontrada para os parâmetros digitados!" << endl;
    }
    
}

unsigned int BaseGeoIP::str2ip(const string & ip) {
    istringstream inp(ip);
 
    unsigned int o1, o2, o3, o4;
 
    inp >> o1; // lê primeiro número
    inp.ignore(1); // ignora o ponto
    inp >> o2; // lê segundo número
    inp.ignore(1); // ignora o ponto
    inp >> o3; // lê terceiro número
    inp.ignore(1); // ignora o ponto
    inp >> o4; // lê quarto número
 
    if (inp.fail()) throw -1; // erro de conversão !!!
 
    return (o1<<24) + (o2<<16) + (o3<<8) + o4;
}
 
string BaseGeoIP::ip2str(unsigned int addr) {
    unsigned int o1, o2, o3, o4;
    ostringstream out;
 
    o1 = addr >> 24; // extrai o primeiro número
    o2 = (addr >> 16) & 0xff; // extrai o segundo número 
    o3 = (addr >> 8) & 0xff; // extrai o terceiro número
    o4 = addr & 0xff; // extrai o quatro número
 
    // usa um stringstream de escrita para gerar uma string contendo
    // o endereço IP em formato decimal separado por pontos
    out << o1 << '.' << o2 << '.' << o3 << '.' << o4;
 
    return out.str();
}