#ifndef LISTA_H
#define	LISTA_H
#include <typeinfo> 
#include <ostream>
#include <iostream>
#include "string.h"
#include <locale>
 
using namespace std;
 
// uma classe template para nodos da lista ...
template <class T> struct Nodo {
  T dado;
  Nodo<T> * proximo;
 
  // um construtor para criar um Nodo facilmente ...
  Nodo(const T & umDado);
};
 
// a classe template para a lista ...
template <class T> class Lista {
 private:
  // ponteiros para o primeiro e último nodos da lista
  Nodo<T> * inicio, * ultimo, * atual;  
 
  // a quantidade de nodos existente na lista
  int comp;
 public:
  //construtor: não precisa de parâmetros para criar uma nova lista
  Lista();
 
  // construtor de cópia
  Lista(const Lista& outra);
 
  // destrutor
  ~Lista();
 
  // adiciona "algo" no inicio da lista
  void adiciona(const T & algo);
 
  // adiciona "algo" no final da lista
  void anexa(const T & algo);
 
  // adiciona "algo" em uma posição específica da lista  
  void insere(const T & algo, int posicao);
 
  // remove o dado que está na "posicao" na lista, e retorna 
  // uma cópia desse dado
  T remove(int posicao);
 
  // remove o dado que for equivalente a "algo", e retorna 
  // uma cópia desse dado
  T retira(const T & algo);
 
  // estas duas operações são idênticas: retorna
  // uma referência ao dado que está na "posicao" na lista
  T& obtem(int posicao) const;
  
  
  T& operator[](int pos) const;
 
  // estes operadores podem ser implementados depois
  Lista& operator=(const Lista& outra);
  bool operator==(const Lista<T> & outra) const;
 
 
  // Retorna uma referência a um dado que seja equivalente a "algo"
  T& procura(const T &algo) const; 
 
  // Procura todos os dados equivalentes a "algo", e os
  // anexa a "lista". Retorna uma referência a "lista".
  Lista<T> & procuraMuitos(const T &algo, Lista<T> & lista) const;
 
  // retorna a quantidade de dados armazenados na lista
  int comprimento() const;
 
  // retorna true se lista estiver vazia
  bool vazia() const;
 
  // Esvazia a lista
  void esvazia();
 
  // apresenta o conteúdo da lista no stream "out"
  void escrevaSe(ostream & out) const;
  void escrevaSe(ostream & out, char delim) const;
 
  // ordena a lista
  //void ordena(); 
  
  // Método ordenaBolha: faz o ordenamento de uma lista usando bubble sort  
  void ordenaBolha();
  
  // Método ordenaSelecao: faz o ordenamento de uma lista usando bubble sort
  void ordenaSelecao();
  
  void insereOrdenado(const T & algo);
  
  void ordenaInsercao();
  
  // inicia uma iteração
  void inicia();
   // retorna uma referência ao próximo dado da iteração
  // se não houver mais dados, gera uma exceção
  T& proximo();
  
   // retorna verdadeiro se a iteração terminou (chegou ao fim da lista)
  bool fim() const;
  
  void inverte();
};

template <typename T> Nodo<T>::Nodo(const T & umDado) {
    proximo = NULL;
    dado = umDado;
}
 
template <typename T> Lista<T>::Lista() {
   inicio = NULL;
   ultimo = NULL;
   comp = 0; //comprimento
   
   /* O ponteiro this é intrínseco do objeto criado. Ele aponta para ele mesmo
   this->inicio = NULL;
   this->ultimo = NULL;
   this->comp = 0; //comprimento
    */
}

template <typename T> Lista<T>::Lista(const Lista<T> & outra) {
    inicio = NULL;
    ultimo = NULL;
    comp = 0;
    
    *this = outra;
}
 
template <typename T> Lista<T>::~Lista() {
}
 
template <typename T> void Lista<T>::adiciona(const T& algo) { //adiciona no início
    Nodo<T> * nodo = new Nodo<T>(algo);
    nodo->proximo = inicio;
    inicio = nodo;
    if (ultimo == NULL) ultimo = nodo;
    comp++;

}
 
template <typename T> void Lista<T>::anexa(const T& algo) { //adiciona no fim
    Nodo<T> * nodo = new Nodo<T>(algo);
    nodo->proximo = NULL;
    if(comp == 0){
        inicio = nodo;
    } else {
        ultimo->proximo = nodo;
    }
    ultimo = nodo;
    comp++;

}
 
template <typename T> int Lista<T>::comprimento() const {
return comp;
}

 
template <typename T> void Lista<T>::esvazia() {
    while (!vazia()){
        remove(0);
    }
}
 
template <typename T> void Lista<T>::insere(const T& algo, int posicao) { //adiciona no meio
    if (posicao == 0) adiciona(algo);
    else {
        Nodo<T> * nodo = new Nodo<T>(algo);
        Nodo<T> * nodotemp = inicio;
        for (int i = 1; i < posicao; i++){
            nodotemp = nodotemp->proximo;
    }
    nodo->proximo = nodotemp->proximo;
    nodotemp->proximo = nodo;
    comp++;
    }
}
 
template <typename T> T& Lista<T>::obtem(int posicao) const {
    Nodo<T> * nodotemp = inicio;
    for (int i = 1; i <= posicao; i++){
        nodotemp = nodotemp->proximo;
    }
    return nodotemp->dado;
   
}
 
template <typename T> T& Lista<T>::operator[](int pos) const {
    return obtem(pos);
 
}
//cada pacote numa linha \/ 
template <typename T> void Lista<T>::escrevaSe(ostream& out) const {
	for (Nodo<T> * ptr = inicio; ptr != NULL; ptr = ptr->proximo) {
		out << ptr->dado << endl;
	}
}
 
template <typename T> void Lista<T>::escrevaSe(ostream& out, char delim) const {
	Nodo <T> * ptr;

	for (ptr = inicio; ptr !=NULL; ptr = ptr->proximo) {
		out <<ptr->dado <<delim;
	}
}
 
template <typename T> T Lista<T>::remove(int posicao) {
    if (posicao == 0) {
        Nodo<T> * nodoadeletar = inicio;
        T dado = nodoadeletar->dado;
        inicio = inicio->proximo;
        
        if(comp==1){
            ultimo = NULL;
        }
        
        delete nodoadeletar; 
        comp--;
        
        return dado;  
    }
    Nodo<T> * nodotemp = inicio;
    for (int i = 1; i < posicao; i++) {
        if(nodotemp->proximo==NULL){
              throw -1;
        } else {
                 nodotemp = nodotemp->proximo;
         }
    }
    Nodo<T> * nodoadeletar = nodotemp->proximo;
    nodotemp->proximo = nodoadeletar->proximo; //acesso o caminho onde está o nodotem-> proximo antigo e pego a informação, daí armazeno ela no novo nodotemp->proximo
    
    if(posicao == comp-1){
        ultimo = nodotemp;
    }
    T dado = nodoadeletar->dado;
    delete nodoadeletar; 
    comp--;
    return dado;
}

template <typename T> T Lista<T>::retira(const T& algo) {
    Nodo<T> * nodotemp = inicio;
    if (algo == nodotemp->dado){
        return remove(0);
    }
    for (int i = 1; i < comp; i++){
        nodotemp = nodotemp->proximo;
        if (nodotemp->dado == algo){
            return remove(i);
        }
    }
    return algo;
}
 
template <typename T> bool Lista<T>::vazia() const {
    if (comp == 0){
        return 1;
    } 
    return 0;
    
}
 
 template <typename T> void Lista<T>::ordenaBolha() { //organiza de forma crescente
    for (int j = comp-1; j > 0; j--){
        Nodo<T> * nodo = inicio;
        for(int k = 0; k<j; k++){
            T & dadotemp1 = nodo->dado;
            T & dadotemp2 = nodo->proximo->dado;
            if (dadotemp2 < dadotemp1){
                T inverte = dadotemp1; //inverte recebe valor que esta no dadotemp1
                dadotemp1 = dadotemp2;
                dadotemp2 = inverte;  
            }
            nodo = nodo->proximo;
        }
    }    
}


   
template <typename T> void Lista<T>::ordenaSelecao() {
    Nodo<T> * nodoaux;
    Nodo<T> * nodoaux2;
    for (nodoaux = inicio; nodoaux->proximo != NULL; nodoaux = nodoaux->proximo) {
        Nodo <T> *menor = nodoaux;
        for (nodoaux2 = nodoaux->proximo; nodoaux2 != NULL; nodoaux2 = nodoaux2->proximo) {
            if (nodoaux2->dado < menor->dado) {
                menor = nodoaux2;
            }
        }
        T aux = menor->dado;
        menor->dado = nodoaux->dado;
        nodoaux->dado = aux;
    }
}

template <typename T> void Lista<T>::insereOrdenado(const T & algo) {
    Nodo<T> * nodoaux;
    int cont = 0;
    for (nodoaux = inicio; nodoaux != NULL; nodoaux = nodoaux->proximo) {
        if (algo < nodoaux->dado) {
            insere(algo, cont);
            return;
        }
        if (nodoaux->proximo == NULL) {
            anexa(algo);
            return;
        }
        cont++;
    }
}

template <typename T> void Lista<T>::ordenaInsercao() {
    Lista<T> listaTemp = this;
    this->esvazia();
 
    while(!listaTemp.vazia()){
        this->insereOrdenado(listaTemp.remove(0));
    }
}

template <typename T> T& Lista<T>::procura(const T& algo) const {
    Nodo<T> * nodotemp = inicio;
    if (algo == nodotemp->dado){
        return nodotemp->dado;
    }
    for (int i = 1; i < comp; i++){
        nodotemp = nodotemp->proximo;
        if (nodotemp->dado == algo){
            return nodotemp->dado;
        }
    }
 throw -1;   
 
} 
 
template <typename T> Lista<T>& Lista<T>::procuraMuitos(const T& algo, Lista<T>& lista) const {
    
}

template <typename T> Lista<T>& Lista<T>::operator=(const Lista& outra) {
    esvazia();
    inicio = NULL;
    ultimo =  NULL;
    comp = 0;
    
    for (int i = 0; i < outra.comp; i++){
        anexa(outra.obtem(i));
    }
      
    return *this;
}
 
template <typename T> bool Lista<T>::operator==(const Lista<T>& outra) const {
    if (comp == outra.comp){
        for (int i = 0; i < comp ; i++){
            if (obtem(i) != outra.obtem(i)){
                return false;
            }
        } 
    } else {
        return false;
      }
    return true;
}

template <typename T> void Lista<T>::inicia() {
    atual = inicio;     
}


template <typename T> T& Lista<T>::proximo() {
    if(atual != NULL){
        T * mostra;
        mostra = &(atual->dado);
        atual = atual->proximo;
        return * mostra; 
    } else {
        throw -1;
    }
}

template <typename T> bool Lista<T>::fim() const {
    if (atual == NULL){
        return 1;
    }
    return 0;
}

template <typename T> void Lista<T>::inverte() {
    if(comprimento()==0) { return; }
    Nodo<T> * nodostemp[comprimento()];
    
    Nodo<T> * nodotemp = inicio;
    for(int i = 0; i < comprimento(); i++){ // coloca as referencias pros nodos no vetor de ponteiros
        nodostemp[i] = nodotemp;
        nodotemp = nodotemp->proximo;
    }
    
    
    inicio = nodostemp[comprimento()-1];
    ultimo = nodostemp[0];
    ultimo->proximo = NULL;
    nodotemp = inicio;
    for(int i = comprimento()-1; i > 0; i--){
        nodotemp->proximo = nodostemp[i-1];
        nodotemp = nodotemp->proximo;
    }
    
}

#endif	/* LISTA_H */
