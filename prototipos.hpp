#pragma once
enum Tipo { PREGUNTA,INTERMEDIARIO,CONCLUSION };
enum Valor { SINVALOR = -1, VERDADERO = 1, FALSO = 0};
enum Donde { INICIO, MIFA };
#define CONJUNCION true
#define DISYUNCION false
template <typename Type> struct conclusion;
template <typename Type> struct pregunta;
template <typename Type> struct conclusion_aux;
template <typename Type> struct conclusion_l;
template <typename Type> class sistema_experto;
//template <typename Type> class lista_conclusion_aux;
//template <typename Type> class lista_preguntas;
//template <typename Type> class lista_conclusiones;
