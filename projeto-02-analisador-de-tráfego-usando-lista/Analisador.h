/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Analisador.h
 * Author: schaiana
 *
 * Created on 29 de Maio de 2016, 15:44
 */

#ifndef ANALISADOR_H
#define ANALISADOR_H

#include "Capturador.h"
#include <limits>
#include <string>
#include <time.h>

using namespace std;

struct Fluxo {
    // endereços IP de origem e destino
    in_addr src, dest;
    // ports de origem e destino
    u_short sport, dport;
    // identificador do protocolo cujo pacote está contido no datagrama IP
    u_char proto;
    // atributo para contar coisas (ex: quantidade de pacotes do fluxo, 
    // quantidade de bytes, ... o que for necessário)
    unsigned long cnt;
 
    // cria um Fluxo com os atributos zerados
    Fluxo() {
      src.s_addr = 0;
      dest.s_addr = 0;
      sport = 0;
      dport = 0;
      proto = 0; 
      cnt = 0;
    }
 
    // cria um fluxo a partir de um pacote capturado
    Fluxo(const Frame & f) {
        // verifica se o pacote é um datagrama IP
        if (f->get_type() != Ethernet::type_IP) throw -1;
 
        // obtém o datagrama IP
        IP * ip = (IP*)f->get_payload();
 
        // obtém os endereços ip de origem e destino
        src = ip->get_src();
        dest = ip->get_dest();
 
        // obtém o número do protocolo do payload do datagrama IP (6=TCP, 17=UDP)
        proto = ip->get_proto();
 
        // se for TCP
        if (proto == IP::proto_TCP) {
            // obtém o pacote TCP contido no datagrama IP
            TCP * tcp = (TCP*)ip->get_payload();
            
            // obtém os ports de origem e destino do pacote TCP
            sport = tcp->get_sport();
            dport = tcp->get_dport();
        } else if (proto == IP::proto_UDP) {
            // obtém o pacote UDP contido no datagrama IP
            UDP * udp = (UDP*)ip->get_payload();
 
            // obtém os ports de origem e destino do pacote UDP
            sport = udp->get_sport();
            dport = udp->get_dport();            
        } else throw -1;
 
        cnt = 0;
    }
 
    // compara se dois fluxos são iguais ...
    bool operator==(const Fluxo & outro) const {
        if(src.s_addr!=outro.src.s_addr){
            return false;
        } else if(dest.s_addr!=outro.dest.s_addr){
            return false;
        } else if(sport!=outro.sport){
            return false;
        } else if(dport!=outro.dport){
            return false;
        } else if(proto!=outro.proto){
            return false;
        }
        return true;
    }    
 
    // compara se este fluxo é menor que outro: ex:
    // pode-se considerar a quantidade de pacotes do fluxo,
    // ou de bytes transferidos (para isso pode-se usar o atributo cnt)
    bool operator<(const Fluxo & outro) {
        if(cnt<outro.cnt) {
            return true;
        } else {
            return false;
        }
    }
 
};

class Analisador {
public:
    Analisador();
    Analisador(const Analisador& orig);
    virtual ~Analisador();
    
    Lista<Frame>* capturaPacotesInterface(string interface, int nPacotes);
    Lista<Frame>* carregaArquivo(string arquivo, int nPacotes);
    void salvaArquivo(Lista<Frame>& lista, string nomeArquivo);
    void limpar();
    Lista<string> mostrarQuantosPacotesPorTamanho(Lista<Frame>& lista);
    Lista<string> contarEidentificarFluxos(Lista<Frame>& lista);
private:
    void pausa();
    Capturador* cap;
};

#endif /* ANALISADOR_H */

