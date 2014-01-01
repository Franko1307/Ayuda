#pragma once
#include "prototipos.hpp"
#include "lista_conclusiones_aux.hpp"
#include <iostream>

template <typename Type> struct conclusion {
  Type _conclusion;
  size_t cuantos;
  size_t total;
  Valor valor;
  lista_conclusion_aux<Type> *salientes;
  conclusion<Type> *sig_conclusion;
  conclusion<Type> *ant_conclusion;
  bool intermedio;
  bool conector;
};
template <typename Type> struct conclusion_l{
  Type _conclusion;
  conclusion_l<Type> *ant_conclusion;
  conclusion_l<Type> *sig_conclusion;
  conclusion<Type> *dir_conclusion;
};
template <typename Type> struct pregunta {
  Type _pregunta;
  Valor valor;
  lista_conclusion_aux<Type> *salientes;
  pregunta<Type> *sig_pregunta;
  pregunta<Type> *ant_pregunta;
};
template <typename Type> struct conclusion_aux {
  Type _conclusion;
  bool cambiar;
  conclusion<Type> *dir_conclusion;
  conclusion_aux<Type> *sig_conclusion_aux;
  conclusion_aux<Type> *ant_conclusion_aux;
};
