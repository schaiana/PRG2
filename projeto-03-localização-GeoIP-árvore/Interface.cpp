#include <unistd.h>
#include "Interface.h"


Interface::Interface() {
}

Interface::Interface(const Interface& orig) {
}

Interface::~Interface() {
}

void Interface::mostraMenu(){
    cout << endl << endl << "---- Menu Principal ----" << endl;
    cout << "1) Fazer sua pesquisa na base GeoIP." << endl;
    cout << "2) Fazer sua pesquisa em arquivos salvos anteriormente." << endl;
    cout << "3) Sair." << endl;
    cout << endl << "Digite uma opção: ";
    
    int opcao;
    cin >> opcao;
    
    switch (opcao){
        case 1:
            mostraMenu2("GeoLiteCity-Blocks.csv", "GeoLiteCity-Location.csv", 1);
            break;
            
        case 2: { 
                cout << endl << "Digite o nome do arquivo de blocos de IP: ";
                string arquivo1Captura;
                cin >> arquivo1Captura;
                cout << endl << "Digite o nome do arquivo de localidades: ";
                string arquivo2Captura;
                cin >> arquivo2Captura;

                mostraMenu2(arquivo1Captura, arquivo2Captura, 0);
        }
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "Opçao não encontrada!!!" << endl;
    }
}



void Interface::mostraMenu2(string arqbloc, string arqloc, bool embaralhar){
    BaseGeoIP minhaBase;
    // se embaralhar for 1 faz o "sort" antes de carregar arquivo
    minhaBase.carregaArquivoBloc(arqbloc, embaralhar); // carrega arquivo de blocos na BaseGeoIP
    minhaBase.carregaArquivoLoc(arqloc, embaralhar); // carrega arquivo de localidades na BaseGeoIP
    
    while (1) {
        cout << endl;
        cout << "1) Pesquisar localidade / bloco de endereços por endereço de IP." << endl;
        cout << "2) Pesquisar blocos de endereço de uma determinada localidade." << endl;
        cout << "3) Salvar os arquivos balanceados." << endl;
        cout << "4) Voltar ao menu principal." << endl;
        cout << endl << "Digite uma opção: ";

        int opcao;
        cin >> opcao;

        cout << endl;
        
        switch(opcao){
            case 1: { //pesquisa por IP
                cout << "Digite o endereço de IP: " << endl;
                string IPdigitado;
                cin >> IPdigitado;
                cout << "Pesquisando IP..." << endl;
                minhaBase.procuraIP(IPdigitado, cout);
            }
            break;
            
            case 2: { //pesquisa por pais e/ou cidade
                cout << "Caso não queira pesquisar por um dos parâmetros, digite zero na opção" << endl;
                cout << "Digite a sigla do país: " << endl;
                cout << "(Ex: BR para Brasil, CA para Canadá, IT para Itália)" << endl;
                
                string paisDigitado; 
                cin >> std::ws; // discarta caracteres em branco da entrada
                getline(cin, paisDigitado);

                cout << "Digite a cidade: " << endl;
                cout << "(Ex: Florianópolis, São José, Rio De Janeiro)" << endl;
                
                string cidadeDigitada;
                cin >> std::ws; // discarta caracteres em branco da entrada
                getline(cin, cidadeDigitada);
                
                cout << "Pesquisando localidade..." << endl;
                minhaBase.procuraLoc(paisDigitado, cidadeDigitada, cout);
                
            }
            break;
        
            case 3: { // salva arvores balanceadas em arquivos
                cout << "Digite o nome do arquivo em que serão salvos os blocos de IP balanceados: " << endl;
                string nomeArquivoBloc;
                cin >> nomeArquivoBloc;
                cout << "Salvando arquivo de blocos..." << endl;
                minhaBase.salvaArquivoBloc(nomeArquivoBloc);
                cout << "Digite o nome do arquivo em que serão salvas as localidades balanceadas: " << endl;
                string nomeArquivoLoc;
                cin >> nomeArquivoLoc;
                cout << "Salvando arquivo de localidades..." << endl;
                minhaBase.salvaArquivoLoc(nomeArquivoLoc);
                
                
            }
                break;
            case 4:
                {
                    minhaBase.limpar();
                    return;
            } 
                break;
            default:
                break;
        }
    }
}
