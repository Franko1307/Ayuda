#pragma once

#include "prototipos.hpp"
#include "estructuras.hpp"

template <typename Type> class lista_conclusion_aux{
  conclusion_aux<Type> *principio;
  conclusion_aux<Type> *final;
public:
  lista_conclusion_aux() : principio(NULL), final(NULL){}
  ~lista_conclusion_aux();
  void agregar(conclusion<Type>*,bool);
  bool es_relevante();
  conclusion_aux<Type> *buscar(Type);
  void pintar();
  conclusion_aux<Type> *obtener_principio(){return principio;}
};
template <typename Type> lista_conclusion_aux<Type>::~lista_conclusion_aux() {
  conclusion_aux<Type> *aux;
  while (principio) {
    aux = principio;
    principio = principio->sig_conclusion_aux;
    delete aux;
  }
  this->principio = NULL;
  this->final = NULL;
}
template <typename Type> conclusion_aux<Type> *lista_conclusion_aux<Type>::buscar(Type _conclusion_aux) {
  conclusion_aux<Type> *aux = principio;
  while (aux) {
    if (aux->_conclusion == _conclusion_aux)return aux;
    aux = aux->sig_conclusion_aux;
  }
  return NULL;
}
template <typename Type> void lista_conclusion_aux<Type>::agregar(conclusion<Type> *_conclusion, bool cambiar) {
  if (conclusion_aux<Type> *nueva = buscar(_conclusion->_conclusion)) return;

  _conclusion->total++;
  conclusion_aux<Type> *nueva = new conclusion_aux<Type>;
  nueva->dir_conclusion = _conclusion;
  nueva->cambiar = cambiar;
  nueva->_conclusion = _conclusion->_conclusion;
  nueva->sig_conclusion_aux = NULL;
  nueva->ant_conclusion_aux = NULL;

  if (this->principio) {
    nueva->ant_conclusion_aux = final;
    final->sig_conclusion_aux = nueva;
    final = nueva;
  } else {
    principio = nueva;
    final = nueva;
  }

}
template <typename Type> bool lista_conclusion_aux<Type>::es_relevante() {
  conclusion_aux<Type> *aux = principio;
  while (aux) {
    if (aux->dir_conclusion->valor == SINVALOR) return true;
    aux = aux->sig_conclusion_aux;
  }
  return false;
}
template <typename Type> void lista_conclusion_aux<Type>::pintar() {
  conclusion_aux<Type> *aux = principio;
  std::cout << "{ ";
  while (aux) {
    std::cout << aux->_conclusion << " ,";
    aux = aux->sig_conclusion_aux;
  }
  std::cout << "\b }";
}
