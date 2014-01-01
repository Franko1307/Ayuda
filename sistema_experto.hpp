#pragma once
#include "estructuras.hpp"
#include "prototipos.hpp"
#include "lista_preguntas.hpp"
#include "lista_conclusiones.hpp"
#include "lista_recursiva.hpp"
#include <stdlib.h>

template <typename Type> class sistema_experto {
  lista_preguntas<Type> *A;
  lista_conclusiones<Type> *intermedias;
  lista_conclusiones<Type> *conclusiones;
  lista_recursiva<Type> *L;
public:
  sistema_experto();
  ~sistema_experto();
  void te_adivino();
  void decir_respuesta();
  void decir_respuesta_apenas();
  void conectar(Type,Type,bool);
  void agregar_pregunta(Type pregunta) {A->agregar(pregunta);}
  void agregar_conclusion(Type conclusion,bool logo,bool f){conclusiones->agregar(conclusion,logo,f);}
  void agregar_intermedio(Type intermedio,bool logo,bool f){intermedias->agregar(intermedio,logo,f);}
  void enlazar(Type,Type,bool);
  bool procesar(Valor,pregunta<Type>*);
  bool procesar(Valor,conclusion<Type>*);
  void actualiza_conclusion(Valor, const bool, conclusion<Type> *const);
  Valor preguntar(pregunta<Type> *const);

  void pintar(){
    A->pintar();
    intermedias->pintar();
    conclusiones->pintar();
  }


};
template <typename Type> sistema_experto<Type>::sistema_experto() {
  A = new lista_preguntas<Type>();
  intermedias = new lista_conclusiones<Type>();
  conclusiones = new lista_conclusiones<Type>();
  L = new lista_recursiva<Type>();
}
template <typename Type> sistema_experto<Type>::~sistema_experto() {
  delete A;
  delete intermedias;
  delete conclusiones;
}
template <typename Type> void sistema_experto<Type>::te_adivino() {

  pregunta<Type> *preguntas = A->obtener_principio();
  while (preguntas) {
    if (preguntas->salientes->es_relevante())
      if (procesar(preguntar(preguntas),preguntas)) return decir_respuesta();
      else if (L->procesar(*this)) return decir_respuesta();
    preguntas = preguntas->sig_pregunta;
  }
  std::cout << "Parece que no hemos llegado a nada" << std::endl;
  std::cout << "Esto es lo mas probable que sea de lo que dijiste: " << std::endl;
  decir_respuesta_apenas();
}
template <typename Type>
bool sistema_experto<Type>::procesar(const Valor valor, pregunta<Type> *const _pregunta) {
  if (valor == SINVALOR) return false;
  conclusion_aux<Type> *aux = _pregunta->salientes->obtener_principio();

  while (aux) {

    if (aux->dir_conclusion->valor != SINVALOR) {
      aux = aux->sig_conclusion_aux;
      continue;
    }

    actualiza_conclusion(valor,aux->cambiar,aux->dir_conclusion);
    if ((aux->dir_conclusion->valor == VERDADERO || aux->dir_conclusion->valor == FALSO) &&
         aux->dir_conclusion->intermedio) L->agregar(aux->dir_conclusion);
    else if (aux->dir_conclusion->valor == VERDADERO && !aux->dir_conclusion->intermedio ) return true;
    aux = aux->sig_conclusion_aux;
  }
  return false;
}
template <typename Type>
bool sistema_experto<Type>::procesar(const Valor valor, conclusion<Type> *const _pregunta) {
  if (valor == SINVALOR) return false;
  conclusion_aux<Type> *aux = _pregunta->salientes->obtener_principio();

  while (aux) {

    if (aux->dir_conclusion->valor != SINVALOR) {
      aux = aux->sig_conclusion_aux;
      continue;
    }

    actualiza_conclusion(valor,aux->cambiar,aux->dir_conclusion);
    if ((aux->dir_conclusion->valor == VERDADERO || aux->dir_conclusion->valor == FALSO) &&
         aux->dir_conclusion->intermedio) L->agregar(aux->dir_conclusion);
    else if (aux->dir_conclusion->valor == VERDADERO && !aux->dir_conclusion->intermedio ) return true;
    aux = aux->sig_conclusion_aux;
  }
  return false;
}
template <typename Type>
void sistema_experto<Type>::actualiza_conclusion(Valor valor, const bool cambiar, conclusion<Type> *const x) {
    if (cambiar) {
      if (valor == VERDADERO) valor = FALSO;
      else valor = VERDADERO;
    }
    if (x->conector == CONJUNCION && valor == VERDADERO) {
      x->cuantos++;
      if (x->cuantos >= x->total) x->valor = VERDADERO;
    }
    else if (x->conector == CONJUNCION && valor == FALSO) x->valor = FALSO;
    else if (x->conector == DISYUNCION && valor == VERDADERO) x->valor = VERDADERO;
    else { //if (x->conector == DISYUNCION && valor == FALSO)
      x->cuantos++;
      if (x->cuantos >= x->total) x->valor = FALSO;
    }
}
template <typename Type> Valor sistema_experto<Type>::preguntar(pregunta<Type> *const _pregunta) {
  if (system( "cls" )) system( "clear" );
  std::cout << _pregunta->_pregunta << std::endl;
  std::cout << "1) SI" << std::endl;
  std::cout << "2) NO" << std::endl;
  std::cout << "3) NO LO SE" << std::endl;
  int data; std::cin >> data;
  if (data == 1) _pregunta->valor = VERDADERO;
  else if(data == 2) _pregunta->valor = FALSO;
  return _pregunta->valor;
}
template <typename Type> void sistema_experto<Type>::decir_respuesta_apenas() {
  conclusion<Type> *solucion = conclusiones->obtener_mejor_conclusion();
  std::cout << solucion->_conclusion << std::endl;
}
template <typename Type> void sistema_experto<Type>::decir_respuesta() {
  conclusion<Type> *aux = conclusiones->obtener_conclusion();
  std::cout << aux->_conclusion << std::endl;
}
template <typename Type> void sistema_experto<Type>::conectar(Type _pregunt, Type _conclus, bool cambiar) {

  pregunta<Type> *_pregunta = NULL;
  pregunta<Type> *_preguntaaux = NULL;
  conclusion<Type> *_conclusion = NULL;
  if (_pregunta = A->buscar(_pregunt)) {
    if (_conclusion = conclusiones->buscar(_conclus)) _pregunta->salientes->agregar(_conclusion,cambiar);
    else if (_conclusion = intermedias->buscar(_conclus)) _pregunta->salientes->agregar(_conclusion,cambiar);
    //else if (_preguntaaux = A->buscar(_conclus)) _pregunta->salientes->agregar(_preguntaaux,cambiar);
  } else if (_conclusion = intermedias->buscar(_pregunt)) {
    conclusion<Type> *aux;
    if (aux = conclusiones->buscar(_conclus)) _conclusion->salientes->agregar(aux,cambiar);
    else if (aux = intermedias->buscar(_conclus)) _conclusion->salientes->agregar(aux,cambiar);
    //else if (_preguntaaux = A->buscar(_conclus)) _conclusion->salientes->agregar(_preguntaaux,cambiar);
  }
}
