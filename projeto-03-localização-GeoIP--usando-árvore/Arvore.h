#ifndef ARVORE_H
#define ARVORE_H
 
#include <string>
#include <fstream>
#include "Lista.h"
 
using namespace std;
 
// Uma árvore de pesquisa binária: na verdade, um objeto da classe Arvore
// representa um nodo de uma árvore ...
 
template <typename T> class Arvore {
 protected:
  T valor; // valor guardado neste nodo da árvore
  Arvore<T> * esq, * dir; // ramos esquerdo e direito
 public:
  Arvore(const T& data);
  Arvore(const Arvore<T> & outra);
  Arvore();
  ~Arvore();
 
  // adiciona um dado à árvore
  void adiciona(const T & dado);
 
  // "obtem" e "operator[]" são idênticos:
  // obtém um dado que seja igual a "algo"
  T & obtem(const T & algo);
  T & operator[](const T & algo);
  
  // remove um valor da árvore... deixemos isto por último ;-)
  T remove(const T & algo);
 
  // algo mais simples: remove os ramos esquerdo e direito
  void esvazia();
 
  // altura da folha mais profunda
  unsigned int altura() const;
  int fatorb() const;
  
    // rotação esquerda
  Arvore<T> * rotacionaL();
 
  // rotação direita
  Arvore<T> * rotacionaR();
  Arvore<T> * balanceia();
  
  // quantidade de nodos da árvore
  unsigned int tamanho() const;
 
  void escrevaSe(ostream & out) const;
  void escrevaSePreOrder(ostream & out) const;
 
  // retorna a subárvore esquerda ou direita
  Arvore<T> * esquerda() const;
  Arvore<T> * direita() const;
 
  // grava uma cópia dos valores na lista fornecida
  void valores(Lista<T> & lista) const;
 
  // retorna uma referência ao valor da raiz
  T & obtemValor() const {return valor;}
 
  // verifica se "algo" existe na árvore
  bool existe(const T & algo) const;

};

template <typename T> Arvore<T>::Arvore(const T& data){ 
    esq = NULL;
    dir = NULL;
    valor = data;
}

template <typename T> Arvore<T>::~Arvore(){ 

}
  
template <typename T> void Arvore<T>::adiciona(const T & dado){
    Arvore<T> * nodotemp = this;
    while (true){
        if (dado == nodotemp->valor){
            nodotemp->valor = dado;
            break;
        }
        if (dado < nodotemp->valor){
            if (nodotemp->esq == NULL){
                nodotemp->esq = new Arvore<T>(dado);
                break;
            } else {
                nodotemp = nodotemp->esq;
              }     
        } else {
            if (nodotemp->dir == NULL){
                nodotemp->dir = new Arvore<T>(dado);
                break;
            } else {
                nodotemp = nodotemp->dir;
                
            }
            
        }
    }

}

template <typename T> T & Arvore<T>::obtem(const T & algo) {
    Arvore<T> * nodotemp = this;
    while (true){
        if (algo == nodotemp->valor){
            return nodotemp->valor;
        } else if (algo < nodotemp->valor){
            if (nodotemp->esq == NULL){
                throw -1;
            } else {
                nodotemp = nodotemp->esq;
              }
        } else {
            if (nodotemp->dir == NULL){
                throw -1;
            } else {
                nodotemp = nodotemp->dir;
            }
        }
    }
 
}

template <typename T> void Arvore<T>::valores(Lista<T> & lista) const {
    lista.adiciona(valor);
    if (esq) esq->valores(lista);
    if (dir) dir->valores(lista);
}

template <typename T> T Arvore<T>::remove(const T & algo) {
    Arvore<T> * nodotemp = this; //cria um ponteiro para o nodo que vai ser deletado
    Arvore<T> * nodotempanterior = NULL; //cria um ponteiro para o nodo anterior ao que vai ser deletado
    while (true){ //procura pelo nodo a ser deletado
        if (algo == nodotemp->valor){ //nodo igual ao procurado
            break;   
        }
        if (algo < nodotemp->valor){ //nodo procurado menor que o nodo comparado
            if (nodotemp->esq == NULL){
                throw -1;
            }
            nodotempanterior = nodotemp;
            nodotemp = nodotemp->esq;           
        } else { //nodo procurado maior que o nodo comparado
            if (nodotemp->dir == NULL){
                throw -1;
            }
            nodotempanterior = nodotemp;
            nodotemp = nodotemp->dir; 
        }
    } //sai do while quando acha o nodo que vai ser deletado
    
    if (nodotemp->esq == NULL && nodotemp->dir == NULL){ //se os nodos filhos são nulos, armazena dado do nodo, remove o mesmo e reorganiza a árvore
        if (nodotempanterior != NULL){
            nodotempanterior->esq = NULL;
        }
        T valorremovido = nodotemp->valor;
        delete nodotemp;
        return valorremovido;
        
    }
    
    if (nodotemp->esq == NULL){ //se o nodo filho da esquerda é nulo, armazena dado do nodo, remove o mesmo e reorganiza a árvore
        T valorremovido = nodotemp->valor;
        if (nodotempanterior != NULL){
            nodotempanterior->esq = nodotemp->dir;          
        }
        delete nodotemp;
        return valorremovido;
    } else { //se o nodo filho da esquerda não é nulo
        if (nodotemp->esq->dir == NULL){ // colocar o filho da direita do nodo que vai ser removido como filho da direita do que vai assumir o lugar dele
            T valorremovido = nodotemp->valor;
            nodotemp->esq->dir = nodotemp->dir;
            if (nodotempanterior != NULL){ //se o nodo removido é filho de algum nodo
                if (nodotemp->valor < nodotempanterior->valor){ //e o nodo removido está à esquerda do nodopai
                    nodotempanterior->esq = nodotemp->esq; //atribui o nodo à esquerda do nodo a ser removido ao nodo da esquerda do nodopai
                } else { //e o nodo removido está à direita do nodopai
                    nodotempanterior->dir = nodotemp->esq; //atribui o nodo à direita do nodo a ser removido ao nodo da esquerda do nodopai
                  }
                delete nodotemp; //deleta o nodo
            } else {
                *nodotemp = *nodotemp->esq;
            }
            
            
            return valorremovido; //retorna valor deletado
            
        } else{ //se o nodo filho da esquerda não é nulo e o nodo->esq->dir não for nulo, procura pelo valor imediatamente menor ao que vai ser removido
            Arvore<T> * nodotempproximo = nodotemp->esq;
            Arvore<T> * anteriornodotempproximo = nodotemp->esq;
            while (true){
                if (nodotempproximo->dir == NULL){
                    break;            
                } else {
                    anteriornodotempproximo = nodotempproximo;
                    nodotempproximo = nodotempproximo->dir;            
                  }
            }
            
            Arvore<T> * nodofilho = nodotempproximo->esq; //filho do nodo que irá substituir o removido
            T valorremovido = nodotemp->valor;
            nodotempproximo->dir = nodotemp->dir;
            nodotempproximo->esq = nodotemp->esq;
            anteriornodotempproximo->dir = nodofilho;
            if (nodotempanterior != NULL){
                nodotempanterior->esq = nodotempproximo;
            }
            delete nodotemp;
            return valorremovido;
        }
        
    
    }
 
}

  // retorna a subárvore esquerda ou direita
  
  
template <typename T>  Arvore<T> * Arvore<T>::esquerda() const {
      
}
  
template <typename T>  Arvore<T> * Arvore<T>::direita() const {
      
}
  
template <typename T> void Arvore<T>::escrevaSe(ostream& out) const {
    static int nivel = -1;
    string prefixo;
 
    nivel++;
    prefixo.append(nivel, ' ');
 
    if (dir) dir->escrevaSe(out);
    out << prefixo << valor << endl;
    if (esq) esq->escrevaSe(out);
    nivel--;
}

template <typename T>  unsigned int Arvore<T>::tamanho() const {
    unsigned int aux = 0;

    if (esq != NULL) aux = aux + esq->tamanho();
    if (dir != NULL) aux = aux + dir->tamanho();
    aux = aux + 1;
    return aux;
            
}


template <typename T>  unsigned int Arvore<T>::altura() const {
    if (esq == NULL && dir == NULL){
        return 0;
    } else {
        unsigned int alturaesq = 0;
        unsigned int alturadir = 0;
        if (esq != NULL){
            alturaesq = esq->altura();           
        }
        if (dir != NULL){
            alturadir = dir->altura();
        }
        if (alturaesq < alturadir){
            return 1 + alturadir;
        } else {
            return 1 + alturaesq;
           }
     }
            
}

template <typename T>  int Arvore<T>::fatorb() const {
    if (esq == NULL && dir == NULL){
        return 0;
    } else {
        int alturaesq = 0;
        int alturadir = 0;
        if (esq != NULL){
            alturaesq = esq->altura()+1;
        }
        if (dir != NULL){
            alturadir = dir->altura()+1;
        }
       return  alturaesq - alturadir;  
    }  
}

template <typename T>  Arvore<T> * Arvore<T>::balanceia() {
    Arvore<T> * nodotemp = this;
    
    if (nodotemp->esq) {
        nodotemp->esq = nodotemp->esq->balanceia();     
    }
    if (nodotemp->dir) {
        nodotemp->dir = nodotemp->dir->balanceia();       
    }

    while (nodotemp->fatorb() < -1) {
        if (nodotemp->dir->fatorb() > 0){
            nodotemp->dir = nodotemp->dir->rotacionaR();
        } 
        nodotemp = nodotemp->rotacionaL();
        nodotemp->fatorb();
    }
    
    while (nodotemp->fatorb() > 1) {
        if (nodotemp->esq->fatorb() < 0){
            nodotemp->esq = nodotemp->esq->rotacionaL();
        }
        nodotemp = nodotemp->rotacionaR();
        nodotemp->fatorb();
    }
    
    return nodotemp;
}

template <typename T>  Arvore<T> * Arvore<T>::rotacionaL() {
    Arvore<T> * nodotemp = this; 
    Arvore<T> * aux = this;
    
    if (dir){
        aux = aux->dir;
        nodotemp->dir = aux->esq;
        aux->esq = nodotemp;
    }
    
    return aux;
   
}

template <typename T>  Arvore<T> * Arvore<T>::rotacionaR() {
    Arvore<T> * nodotemp = this; 
    Arvore<T> * aux = this;
    
    if (esq){
        aux = aux->esq;
        nodotemp->esq = aux->dir;
        aux->dir = nodotemp;
        
    }
    
    return aux;
}
template <typename T> void Arvore<T>::escrevaSePreOrder(ostream& out) const {
    out << valor << endl;
    if (esq) esq->escrevaSePreOrder(out);
    if (dir) dir->escrevaSePreOrder(out);

}
#endif

//iterador tem que ser não recursivo, usar pilha
