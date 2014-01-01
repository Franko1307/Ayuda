#pragma once

#include "sistema_experto.hpp"
#include "prototipos.hpp"
#include "estructuras.hpp"
template <typename Type> class lista_recursiva {
  conclusion_l<Type> *principio;
  conclusion_l<Type> *final;
public:
  lista_recursiva() : principio(NULL), final(NULL){}
  ~lista_recursiva();
  void agregar(conclusion<Type>*);
  void sacar();
  bool procesar(sistema_experto<Type> &);
  bool buscar(Type);
};

template <typename Type> lista_recursiva<Type>::~lista_recursiva() {
  conclusion_l<Type> *aux;
  while (principio) {
    aux = principio;
    principio = aux->sig_conclusion;
    delete aux;
  }
}
template <typename Type> void lista_recursiva<Type>::agregar(conclusion<Type> *_conclusion) {
  if (buscar(_conclusion->_conclusion)) return;
  conclusion_l<Type> *nuevo = new conclusion_l<Type>;
  nuevo->dir_conclusion = _conclusion;
  nuevo->ant_conclusion = NULL;
  nuevo->sig_conclusion = NULL;
  nuevo->_conclusion = _conclusion->_conclusion;

  if (principio) {
    nuevo->ant_conclusion = final;
    final->sig_conclusion = nuevo;
    final = nuevo;
  } else {
    principio = nuevo;
    final = nuevo;
  }
}
template <typename Type> void lista_recursiva<Type>::sacar() {
  conclusion_l<Type> *aux = principio;
  principio = aux->sig_conclusion;
  delete aux;
}
template <typename Type> bool lista_recursiva<Type>::procesar(sistema_experto<Type> &sistema) {

  while (principio) {
      if (sistema.procesar(principio->dir_conclusion->valor, principio->dir_conclusion)) return true;
      sacar();
  }
  return false;
}
template <typename Type> bool lista_recursiva<Type>::buscar(Type var) {
  conclusion_l<Type> *aux = principio;
  while (aux) {
    if (aux->_conclusion == var) return true;
    aux = aux->sig_conclusion;
  }
  return false;
}
