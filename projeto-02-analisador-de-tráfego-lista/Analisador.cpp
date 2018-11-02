/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Analisador.cpp
 * Author: schaiana
 * 
 * Created on 29 de Maio de 2016, 15:44
 */

#include <unistd.h>
#include <stdlib.h>

#include "Analisador.h"

using namespace std;

Analisador::Analisador() {
    cap = NULL;
}

Analisador::Analisador(const Analisador& orig) {
}

Analisador::~Analisador() {
}

Lista<Frame>* Analisador::capturaPacotesInterface(string interface, int nPacotes){
    try{
        cap = new Capturador(1518, interface.c_str());  
        Lista<Frame>* pkts = new Lista<Frame>;  
        
        unsigned int bytes=0;
        double tempo = 0;
        time_t start = time(0);
        
        for(int i = 0; i<nPacotes; i++){
            Frame pkt = cap->capture();
            bytes += pkt->get_size();
            pkts->anexa(pkt);
            
            tempo = difftime( time(0), start);
            if(tempo==1){
                cout << "Taxa de transferência: " << (bytes/tempo) << " Bps" << endl;
                bytes = 0;
                start = time(0);
            }
        }
        
        return pkts;
    } catch (char* c) {
        cout << "Não foi possível abrir " << interface <<endl <<endl;
        pausa();
        throw -1;
    }
}

Lista<Frame>* Analisador::carregaArquivo(string arquivo, int nPacotes){
    try {
        cap = new Capturador(arquivo.c_str());
        return cap->capture(nPacotes);
    } catch (char* c) {
        
        throw -1;
    }
}

void Analisador::pausa(){
    cout << "Pressione ENTER para continuar." << endl;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

void Analisador::salvaArquivo(Lista<Frame>& lista, string nomeArquivo){
    if (lista.vazia()) return;
    
    ArquivoCaptura * arq = cap->gera_arquivo_captura(nomeArquivo.c_str());

    lista.inicia();

    Ethernet * pkt;
    int i = 0;
    while (!lista.fim()){
        // obtém o próximo pacote capturado
        pkt = lista.proximo().get_frame();
        // grava o pacote no arquivo de captura
        arq->adicione(pkt);
 
    }
    delete arq;
}

void Analisador::limpar(){
    if(cap!=NULL){
        delete cap;
        cap = NULL;
    }
}

Lista<string> Analisador::mostrarQuantosPacotesPorTamanho(Lista<Frame>& lista){
    int contaPacotes[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    lista.inicia();
    
    while(!lista.fim()){
        Frame & pacote = lista.proximo();
        u_short tamanho = pacote->get_size();
        if(tamanho >=0 && tamanho<=100){
            contaPacotes[0]++;
        } else if(tamanho >100 && tamanho<=200){
            contaPacotes[1]++;
        } else if(tamanho >200 && tamanho<=300){
            contaPacotes[2]++;
        } else if(tamanho >300 && tamanho<=400){
            contaPacotes[3]++;
        } else if(tamanho >400 && tamanho<=500){
            contaPacotes[4]++;
        } else if(tamanho >500 && tamanho<=600){
            contaPacotes[5]++;
        } else if(tamanho >600 && tamanho<=700){
            contaPacotes[6]++;
        } else if(tamanho >700 && tamanho<=800){
            contaPacotes[7]++;
        } else if(tamanho >800 && tamanho<=900){
            contaPacotes[8]++;
        } else if(tamanho >900 && tamanho<=1000){
            contaPacotes[9]++;
        } else if(tamanho >1000 && tamanho<=1100){
            contaPacotes[10]++;
        } else if(tamanho >1100 && tamanho<=1200){
            contaPacotes[11]++;
        } else if(tamanho >1200 && tamanho<=1300){
            contaPacotes[12]++;
        } else if(tamanho >1300 && tamanho<=1400){
            contaPacotes[13]++;
        } else if(tamanho >1400 && tamanho<=1500){
            contaPacotes[14]++;
        }
    }
    
    Lista<string> listaRetorno;
    
    for(int i =0; i<15; i++){
        string strTemp = to_string(contaPacotes[i]) + " Pacotes de " + to_string(i*100) +" a " + to_string(i*100+100) +" Bytes";
        listaRetorno.anexa(strTemp);
    }
    return listaRetorno;
}

Lista<string> Analisador::contarEidentificarFluxos(Lista<Frame>& lista){
    Lista<Fluxo> listaTempFluxos;
    lista.inicia();
    
    while(!lista.fim()){
        try{
            Frame & pacote = lista.proximo();
            Fluxo fluxo(pacote);
            if(listaTempFluxos.vazia()){
                fluxo.cnt=pacote->get_size();
                listaTempFluxos.adiciona(fluxo);
            } else {
                try {
                    Fluxo & fluxoTemp = listaTempFluxos.procura(fluxo);
                    fluxoTemp.cnt+=pacote->get_size();
                } catch (int i){
                    listaTempFluxos.anexa(fluxo);
                }
            }
        } catch (int i){
        
        }
    }
    listaTempFluxos.ordenaSelecao();
    listaTempFluxos.inverte();
    
    Lista<string> listaRetorno;
    
    listaTempFluxos.inicia();

    while(!listaTempFluxos.fim()){
       Fluxo fluxo = listaTempFluxos.proximo();
       string protocolo;
       if (fluxo.proto == IP::proto_TCP){
           protocolo = "TCP";
       } else if (fluxo.proto == IP::proto_UDP){
           protocolo = "UDP";
       }
       string infoFluxo = "Fluxo - IP Origem: " + to_string(fluxo.src.s_addr) + " - IP Destino: " + to_string(fluxo.dest.s_addr) +
                            " - Porta Origem: " + to_string(fluxo.sport) + " - Porta Destino: " + to_string(fluxo.dport) +
                            " - Protocolo: " + protocolo + " - Bytes Transferidos: " + to_string(fluxo.cnt);
       listaRetorno.anexa(infoFluxo); 

    }
    return listaRetorno;
}