/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interface.cpp
 * Author: schaiana
 * 
 * Created on 29 de Maio de 2016, 15:43
 */

#include <unistd.h>

#include "Interface.h"


Interface::Interface() {
}

Interface::Interface(const Interface& orig) {
}

Interface::~Interface() {
}

void Interface::mostraMenu(){
    cout << endl << endl << "==== Menu Principal ====" << endl;
    cout << "1) Nova Captura Online" << endl;
    cout << "2) Carregar Arquivo de Captura" << endl;
    cout << "3) Sair" << endl;
    
    cout << endl << "Digite uma opção: ";
    
    int opcao;
    cin >> opcao;
    
    switch (opcao){
        case 1: {
                if(getuid()!=0){
                    cout << endl << "***Você precisa rodar este programa com privilégios para acessar esta opção***"<<endl<<endl;
                    pausa();
                    break;
                }
                
                cout << endl << "Digite o nome da interface: ";
                string interfaceCaptura;
                cin >> interfaceCaptura;
                
                cout << endl << "Digite o número de pacotes a ser capturado: ";
                cin >> npacotes;
                
                try {
                    taxaCaptura = 0;
                    time_t start = time(0);
                    
                    listaPacotes = meuAnalisador.capturaPacotesInterface(interfaceCaptura, npacotes);
                    double tempoCaptura = difftime( time(0), start);
                    unsigned int tamanhoCaptura = 0;
                    listaPacotes->inicia();
                    
                    while(!listaPacotes->fim()){
                        Frame & pacote = listaPacotes->proximo();
                        tamanhoCaptura+=pacote->get_size();
                    }
                    
                    taxaCaptura = tamanhoCaptura/tempoCaptura;
                    
                    mostraMenu2(true);
                    remove_pktlist(listaPacotes);
                } catch(int i){
                    
                }
            }
            break;
        case 2: {
                cout << endl << "Digite o nome do arquivo: ";
                string arquivoCaptura;
                cin >> arquivoCaptura;
                
                cout << endl << "Digite o número de pacotes a ser capturado: ";
                cin >> npacotes;
                
                try{
                    listaPacotes = meuAnalisador.carregaArquivo(arquivoCaptura, npacotes);
                    mostraMenu2(false);
                    remove_pktlist(listaPacotes);

                } catch (int i) {
                    cout << endl << "Não foi possível abrir o arquivo: " << arquivoCaptura << endl;
                    pausa();
                }
                
                
            }
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "Opçao não encontrada!!!" << endl;
    }
}

void Interface::mostraMenu2(bool ehInterface){
    while (1) {
        cout << endl;
        cout << "1) Salvar captura em arquivo" << endl;
        cout << "2) Apresentar os pacotes em ordem crescente de tamanho" << endl;
        cout << "3) Apresentar os pacotes em ordem descrescente de tamanho" << endl;
        cout << "4) Mostrar quantos pacotes foram transferidos, classificando-os por tamanho (de 100 em 100 bytes)" << endl;
        cout << "5) Contar e identificar os fluxos durante a captura por ordem de quantidade de bytes transferidos"<< endl;
        if(ehInterface){
            cout << "6) Apresentar a taxa de bits ao longo da captura" << endl;
            cout << "7) Voltar ao menu principal" << endl;
        } else {
            cout << "6) Voltar ao menu principal" << endl; 
        }

        cout << endl << "Digite uma opção: ";

        int opcao;
        cin >> opcao;

        cout << endl;
        
        switch(opcao){
            case 1:
                {
                    cout << endl << "Digite o nome do arquivo a ser salvo: ";
                    string nomeArquivo;
                    cin >> nomeArquivo;
                    
                    meuAnalisador.salvaArquivo(*listaPacotes, nomeArquivo);
                    cout << "Arquivo " << nomeArquivo << " salvo!" << endl;
                    pausa();
                }
                break;
            case 2: 
                listaPacotes->ordenaSelecao();
                cout << endl;
                listaPacotes->escrevaSe(cout);
                cout << endl;
                pausa();
                break;
            case 3:
                listaPacotes->ordenaSelecao();
                listaPacotes->inverte();
                cout << endl;
                listaPacotes->escrevaSe(cout);
                cout << endl;
                pausa();
                break;
            case 4: try {
                    Lista<string> listaTamanhos;
                    listaTamanhos = meuAnalisador.mostrarQuantosPacotesPorTamanho(*listaPacotes);
                    listaTamanhos.escrevaSe(cout);
                    cout << endl;
                    pausa();
                } catch (int i) {
                    cout << "Erro ao classificar pacotes por tamanho" << endl;
                }
                break;
            case 5: try {
                        Lista<string> fluxosAnalisados;
                        fluxosAnalisados = meuAnalisador.contarEidentificarFluxos(*listaPacotes);
                        cout << endl << "Número de fluxos: " << fluxosAnalisados.comprimento() << endl<<endl;
                        fluxosAnalisados.escrevaSe(cout);
                        cout << endl;
                        pausa();
                    } catch (int i ) {
                        cout << "Erro ao contar e identificar fluxos" << endl;
                    }
                    break;
            case 6:
                if(!ehInterface) {// volta ao menu principal
                    meuAnalisador.limpar();
                    return;
                } else { // taxa de bytes ao longo da captura
                    cout << "A taxa de captura foi de " << taxaCaptura << " Bytes por segundo" << endl << endl;
                    pausa();
                }
                break;
            case 7:
                if(ehInterface) {// volta ao menu principal
                    meuAnalisador.limpar();
                    return;
                } 
                break;
            default:
                break;
        }
    }
}

void Interface::pausa(){ // pausa o programa até o enter ser pressionado
    cout << "Pressione ENTER para continuar." << endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpa o buffer do cin
    cin.get();
}