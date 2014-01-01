#pragma once

#include <iostream>
#include "prototipos.hpp"
#include "estructuras.hpp"
#include "lista_conclusiones_aux.hpp"

template <typename Type> class lista_conclusiones {
  conclusion<Type> *principio;
  conclusion<Type> *final;
public:
  lista_conclusiones() : principio(NULL), final(NULL){}
  ~lista_conclusiones();
  conclusion<Type> *buscar(Type);
  void agregar(Type,bool,bool);
  void pintar();
  conclusion<Type> *obtener_conclusion();
  conclusion<Type> *obtener_mejor_conclusion();
};
template <typename Type> lista_conclusiones<Type>::~lista_conclusiones() {
  conclusion<Type> *aux;
  while (principio) {
    aux = principio;
    principio = aux->sig_conclusion;
    delete aux;
  }
}
template <typename Type> conclusion<Type> *lista_conclusiones<Type>::obtener_conclusion() {
  conclusion<Type> *aux = principio;
  while (aux) {
    if (aux->valor == VERDADERO) return aux;
    aux = aux->sig_conclusion;
  }
  return NULL;
}
template <typename Type> conclusion<Type> *lista_conclusiones<Type>::buscar(Type _conclusion) {
  conclusion<Type> *aux = principio;
  while (aux) {
    if (aux->_conclusion == _conclusion) return aux;
    aux = aux->sig_conclusion;
  }
  return NULL;
};
template <typename Type> void lista_conclusiones<Type>::agregar(Type _conclusion, bool conector, bool intermedio) {
  if (conclusion<Type> *nueva_conclusion = buscar(_conclusion)) return;
  conclusion<Type> *nueva_conclusion = new conclusion<Type>;
  nueva_conclusion->_conclusion = _conclusion;
  nueva_conclusion->conector = conector;
  nueva_conclusion->intermedio = intermedio;
  nueva_conclusion->cuantos = 0;
  nueva_conclusion->total = 0;
  nueva_conclusion->valor = SINVALOR;
  nueva_conclusion->salientes = new lista_conclusion_aux<Type>;
  nueva_conclusion->sig_conclusion = NULL;
  nueva_conclusion->ant_conclusion = NULL;

  if (this->principio) {
    nueva_conclusion->ant_conclusion = final;
    final->sig_conclusion = nueva_conclusion;
    final = nueva_conclusion;
  } else {
    principio = nueva_conclusion;
    final = nueva_conclusion;
  }

}
template <typename Type> void lista_conclusiones<Type>::pintar() {
  conclusion<Type> *aux = principio;
  while (aux) {
    std::cout << "Conclusion: " << aux->_conclusion;
    std::cout << "Conector: " << aux->conector << std::endl;
    std::cout << "Total: " << aux->total << std::endl;
    std::cout << "Cuantos:" << aux->cuantos << std::endl;
    std::cout << "Valor: " << aux->valor << std::endl;
    std::cout << "Salientes: ";
    aux->salientes->pintar();
    std::cout << std::endl;
    aux = aux->sig_conclusion;
  }
}
template <typename Type> conclusion<Type> *lista_conclusiones<Type>::obtener_mejor_conclusion() {
  conclusion<Type> *iterador = principio;
  conclusion<Type> *mejor = iterador;
  iterador = iterador->sig_conclusion;
  while (iterador) {
    if (iterador->valor == FALSO) {
        iterador = iterador->sig_conclusion;
        continue;
    }
    if (iterador->cuantos > mejor->cuantos) mejor = iterador;
    iterador = iterador->sig_conclusion;
  }
  return mejor;
}
