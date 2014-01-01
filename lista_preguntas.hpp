#pragma once
#include "estructuras.hpp"
#include "prototipos.hpp"
#include "lista_conclusiones_aux.hpp"
#include <iostream>

template <typename Type> class lista_preguntas {
  pregunta<Type> *principio;
  pregunta<Type> *final;
public:
  lista_preguntas() : principio(NULL), final(NULL) {}
  ~lista_preguntas();
  pregunta<Type> *buscar(Type);
  void agregar(Type);
  void pintar();
  pregunta<Type> *obtener_principio(){return principio;}
};
template <typename Type> lista_preguntas<Type>::~lista_preguntas() {
  pregunta<Type> *aux;
  while (principio) {
    aux = principio;
    principio = aux->sig_pregunta;
    delete aux;
  }
  principio = NULL;
  final = NULL;
}
template <typename Type> pregunta<Type> *lista_preguntas<Type>::buscar(Type _pregunta) {
  pregunta<Type> *aux = principio;
  while (aux) {
    if (aux->_pregunta == _pregunta) return aux;
    aux = aux->sig_pregunta;
  }
  return NULL;
};
template <typename Type> void lista_preguntas<Type>::agregar(Type _pregunta) {
  if (pregunta<Type> *nueva_pregunta = buscar(_pregunta)) return;

  pregunta<Type> *nueva_pregunta = new pregunta<Type>;
  nueva_pregunta->_pregunta = _pregunta;
  nueva_pregunta->valor = SINVALOR;
  nueva_pregunta->salientes = new lista_conclusion_aux<Type>;
  nueva_pregunta->sig_pregunta = NULL;
  nueva_pregunta->ant_pregunta =NULL;

  if (principio) {
    nueva_pregunta->ant_pregunta = final;
    final->sig_pregunta = nueva_pregunta;
    final = nueva_pregunta;
  } else {
    principio = nueva_pregunta;
    final = nueva_pregunta;
  }
}

template <typename Type> void lista_preguntas<Type>::pintar() {
  pregunta<Type> *aux = principio;
  while (aux) {
    std::cout << "Pregunta: " << aux->_pregunta << std::endl;
    std::cout << "Valor de verdad" << aux->valor << std::endl;
    std::cout << "Salientes: ";
    aux->salientes->pintar();
    std::cout << std::endl;
    aux = aux->sig_pregunta;
  }
}
