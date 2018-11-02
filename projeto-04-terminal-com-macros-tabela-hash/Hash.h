#ifndef HASH_H
#define HASH_H
 
#include <cstdlib>
#include <string>
#include "Lista.h"
#include "Fila.h"
#include "Pilha.h"
 
using namespace std;
 
template <typename T> class TabelaHash {
 public:
  // cria uma tabela hash com num_linhas linhas
  TabelaHash(int num_linhas);
 
  TabelaHash(const TabelaHash &outra); // construtor de copia
 
  // destrutor
  ~TabelaHash();
 
  // adiciona um dado à tabela. Se já existir na tabela um par contendo a chave
  // "chave", o dado desse par deve ser substituído por "algo". Caso contrário,
  // um novo par deve ser adicionado à tabela.
  void adiciona(const string& chave, const T& algo);
 
  // remove a chave "chave" e o dado a ela associado.
  T remove(const string& chave);
 
  // retorna o dado associado a "chave"
  T& operator[](const string& chave) const;
  T& obtem(const string& chave) const;
 
  // retorna uma lista com as chaves existentes na tabela
  Lista<string> * chaves() const;
 
  // retorna uma lista com os dados existentes na tabela
  Lista<T> * valores() const;
 
  // retorna verdadeiro se "chave" existe na tabela
  bool existe(const string& chave) const; //igual ao obtém, mas retorna só true or false
 
  // esvazia a tabela
  void esvazia();
 
  // retorna a quantidade de dados (ou chaves) existentes na tabela
  int tamanho() const;
 
 private:

 
  // esta struct Par serve para associar uma chave e um dado
  // note que a tabela hash armazena pares (chave, dado)
  struct Par { //chave e valor que vão ser armazenados na tabela
    string chave;
    T valor;
 
    Par(const string& k, const T& dado) {
      chave = k;
      valor = dado;
    }
    Par() {}
    bool operator==(const Par & outro) const{
      return chave == outro.chave;
    }
    

  };
  
        // Atributos da tabela
  Lista<Par> * tab; // vetor de listas ... a tabela propriamente dita !
  int linhas; // a quantidade de linhas da tabela
 
 
  // calcula um valor hash para "chave"
unsigned int hash(const string & chave) const;
};
 
 // Obs: melhores resultados se N for primo !
template <typename T> unsigned int TabelaHash<T>::hash(const string & chave) const {
    int n;
    unsigned int soma = 0;
 
    for (n=0; n < chave.size(); n++) {
      soma = ((soma << 8) + chave[n]) % linhas; 
    }
    return soma % linhas;  
}

template <typename T> TabelaHash<T>::TabelaHash(int num_linhas) {
    linhas = num_linhas;
    tab = new Lista<Par>[linhas];
}
template <typename T> TabelaHash<T>::~TabelaHash() {
    delete[] tab;
}

template <typename T> void TabelaHash<T>::adiciona(const string& chave, const T& algo) {
    unsigned int linha = hash(chave);
    
    Par umPar(chave, algo);
    try {
        Par & outroPar = tab[linha].procura(umPar);
        outroPar.valor = algo; //sobrescreve o valor daquela chave que já existe. Por exemplo atualiza o endereço buscando por um CPF
    } catch (int e){ //se não tiver o par, vai dar uma exceção e adicionar na lista
    tab[linha].adiciona(umPar); //tab é uma lista de linhas
      }
}


template <typename T> T& TabelaHash<T>::obtem(const string& chave) const { //retorna uma referência à chave procurada
    unsigned int linha = hash(chave);
    
    Par umPar;
    umPar.chave = chave;
    Par & outroPar = tab[linha].procura(umPar);
    return outroPar.valor;
    //não precisa de exceção porque o procura da lista já tem
}
template <typename T> T& TabelaHash<T>::operator[](const string& chave) const { //retorna uma referência à chave procurada
    unsigned int linha = hash(chave);
    
    Par umPar;
    umPar.chave = chave;
    Par & outroPar = tab[linha].procura(umPar);
    return outroPar.valor;
    //não precisa de exceção porque o procura da lista já tem
}

template <typename T> bool TabelaHash<T>::existe(const string& chave) const {
    unsigned int linha = hash(chave);
    
    Par umPar;
    umPar.chave = chave;
    try {
        Par & outroPar = tab[linha].procura(umPar);
        return true;
    } catch (int e){
         return false;
      }
     
}
template <typename T> T TabelaHash<T>::remove(const string& chave) {
    unsigned int linha = hash(chave);
    
    Par umPar;
    umPar.chave = chave;
    Par outroPar = tab[linha].retira(umPar);
    return outroPar.valor;   

}

template <typename T> Lista<string> * TabelaHash<T>::chaves() const {
    Lista<string> *l = new Lista<string>;
    
    for (int i = 0; i < linhas; i++) {
        tab[i].inicia();
        while(not tab[i].fim()) {
            Par & umPar = tab[i].proximo();
            l->anexa(umPar.chave);
        }
    }
    return l;
}
template <typename T> Lista<T> * TabelaHash<T>::valores() const {
    Lista<T> *l = new Lista<T>;
    
    for (int i = 0; i < linhas; i++) {
        tab[i].inicia();
        while(not tab[i].fim()) {
            Par & umPar = tab[i].proximo();
            l->anexa(umPar.valor);
        }
    }
    return l;
}

template <typename T> int TabelaHash<T>::tamanho() const {
    int cont = 0;    
    for (int i = 0; i < linhas; i++) {
        tab[i].inicia();
        while(not tab[i].fim()) {
            tab[i].proximo();
            cont++;
        }
    }
    return cont;
    


}


#endif