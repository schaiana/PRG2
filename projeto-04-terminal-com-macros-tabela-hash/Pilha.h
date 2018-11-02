#ifndef PILHA_H
#define PILHA_H

#include <iostream>

using namespace std;

template <typename T> class Pilha {
 public:
  // construtor: deve-se informar a capacidade da pilha
  Pilha(int umaCapacidade);
 
  // construtor de cópia: cria uma pilha que é cópia de outra
  Pilha(const Pilha& outra);
 
  // destrutor da pilha
  ~Pilha();
 
  // operador de atribuição: torna esta pilha uma cópia de outra pilha
  Pilha<T> & operator=(const Pilha<T> & outra);
  bool operator==(const Pilha<T>& outra);
  // operações da pilha
 
  void push(const T & dado); // empilha um dado
 
  T pop(); // desempilha um dado
 
  T& top() const; // retorna o dado do topo da pilha, sem retirá-lo
 
  bool vazia() const { return topo == 0;}
  bool cheia() const {return topo == capacidade;}
  void esvazia(); //deleta os dados da pilha
 protected:
  // atributos da pilha
  T * buffer; // a área de memória para armazenamento da pilha
  int topo, capacidade;
  // outros atributos ???
 
};
 
template <typename T> Pilha<T>::Pilha(int umaCapacidade) {
    topo = 0;
    capacidade = umaCapacidade;
    buffer = new T[umaCapacidade];
}
 
template <typename T> Pilha<T>::Pilha(const Pilha& outra) {
    topo = 0;
    capacidade = 0;
    buffer = new T[0];
    *this = outra;
}
 
template <typename T> Pilha<T>::~Pilha() {
}

template <typename T> Pilha<T>& Pilha<T>::operator=( const Pilha& outra ) {

  // copiar os valores de atributos de "outra"
     capacidade = outra.capacidade;
     topo = outra.topo;
  // alocar memória para "buffer"
     buffer = new T[capacidade]; 
  // copiar conteúdo da "buffer" da "outra" fila
     
     for(int i = 0; i<capacidade; i++){
        (buffer[i]) = (outra.buffer[i]);
     }
     
  // retorna uma referência ao próprio objeto 
  return *this;
}

template <typename T> bool Pilha<T>::operator==(const Pilha<T>& outra){
    if(topo!=outra.topo){
        return 0;
    }
    
    for(int i = 0; i<topo; i++){
        if(buffer[i]!=outra.buffer[i]){
            return 0;
        }
    }   
    return 1;
}

template <typename T> void Pilha<T>::esvazia() {
    while(!vazia()){
        pop();
    }
}
 
template <typename T> void Pilha<T>::push(const T & dado) {
    if(!cheia()){
        buffer[topo] = dado;
        topo++;
    }
}

template <typename T> T Pilha<T>::pop() {
    if(!vazia()){
        T valorTopo = top();
        buffer[topo] = *new T();
        topo = topo-1;
        return valorTopo;
    } else {
        throw -1;
    }
}
 
template <typename T> T& Pilha<T>::top() const{
    if(!vazia()){
        return buffer[topo-1];
    } else {
        throw -1;
    }
}
 
#endif