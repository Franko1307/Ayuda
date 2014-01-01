#include <iostream>
#include "sistema_experto.hpp"
#define NOCAMBIAR false
#define CAMBIAR true
#define CONJUNCION true
#define DISYUNCION false
int main() {
  sistema_experto<std::string> A;
  A.agregar_pregunta("tiene pelo?");
  A.agregar_pregunta("da leche?");
  A.agregar_pregunta("tiene plumas?");
  A.agregar_pregunta("vuela?");
  A.agregar_pregunta("pone huevos?");
  A.agregar_pregunta("come carne?");
  A.agregar_pregunta("tiene dientes agudos?");
  A.agregar_pregunta("tiene garras?");
  A.agregar_pregunta("tiene ojos que miran hacia enfrente?");
  A.agregar_pregunta("tiene pesuniaz?");
  A.agregar_pregunta("rumia?");
  A.agregar_pregunta("es de color leonado?");
  A.agregar_pregunta("tiene manchas obscuras?");
  A.agregar_pregunta("tiene franjas negras?");
  A.agregar_pregunta("tiene patas largas?");
  A.agregar_pregunta("tiene cuello largo?");
  A.agregar_pregunta("es de color blanco?");
  A.agregar_pregunta("es de color blanco y negro?");
  A.agregar_pregunta("nada?");
  //**********************************************++
  //Preguntas
  A.agregar_intermedio("es mamifero",DISYUNCION,true);
  A.agregar_intermedio("es ave", DISYUNCION,true);
  A.agregar_intermedio("d1",CONJUNCION,true);
  A.agregar_intermedio("d2",CONJUNCION,true);
  A.agregar_intermedio("d3",CONJUNCION,true);
  A.agregar_intermedio("d4",CONJUNCION,true);
  A.agregar_intermedio("d5",CONJUNCION,true);
  A.agregar_intermedio("es carnivoro",DISYUNCION,true);
  A.agregar_intermedio("es ungulado",DISYUNCION,true);
  //conclusiones
  A.agregar_conclusion("Es una onza",CONJUNCION,false);
  A.agregar_conclusion("Es un tigre",CONJUNCION,false);
  A.agregar_conclusion("Es una jirafa",CONJUNCION,false);
  A.agregar_conclusion("Es una cebra",CONJUNCION,false);
  A.agregar_conclusion("Es una avestruz",CONJUNCION,false);
  A.agregar_conclusion("Es un pinguino",CONJUNCION,false);
  A.agregar_conclusion("Es un albatros",CONJUNCION,false);
  //conexiones

  //Reglas
  //Tiene pelo o da leche entoces es mamífero.  -V-
  A.conectar("tiene pelo?","es mamifero",NOCAMBIAR);
  A.conectar("da leche?","es mamifero",NOCAMBIAR);
  //Vuela y pone huevos entonces d1 -V-
  A.conectar("vuela?","d1",NOCAMBIAR);
  A.conectar("pone huevos?","d1",NOCAMBIAR);
  //Tiene plumas o d1 entonces es ave -V-
  A.conectar("tiene plumas?","es ave",NOCAMBIAR);
  A.conectar("d1","es ave",NOCAMBIAR);
  //Es mamífero y come carne entonces d2 -V-
  A.conectar("es mamifero", "d2",NOCAMBIAR);
  A.conectar("come carne?","d2",NOCAMBIAR);
  //Tiene dienets agudos y tiene garras y ojos hacia adelante -> d3
  A.conectar("tiene dientes agudos?","d3",NOCAMBIAR);
  A.conectar("tiene garras?","d3",NOCAMBIAR);
  A.conectar("tiene ojos que miran hacia enfrente?","d3",NOCAMBIAR);
  //d2 v d3 -> es carnivoro - v-
  A.conectar("d2","es carnivoro",NOCAMBIAR);
  A.conectar("d3","es carnivoro",NOCAMBIAR);
  //es mamífero y tiene pesuñaz -> d4
  A.conectar("tiene pesuniaz?","d4",NOCAMBIAR);
  A.conectar("es mamifero","d4",NOCAMBIAR);

  //es mamifero y rumia d5
  A.conectar("es mamifero","d5",NOCAMBIAR);
  A.conectar("rumia?","d5",NOCAMBIAR);
  //d4 v d5 -> es ungulado
  A.conectar("d4","es ungulado",NOCAMBIAR);
  A.conectar("d5","es ungulado",NOCAMBIAR);
  //es carnivoro y tiene color leonado y manchas negras -> es una onza
  A.conectar("es carnivoro","Es una onza",NOCAMBIAR);
  A.conectar("es de color leonado?","Es una onza",NOCAMBIAR);
  A.conectar("tiene manchas obscuras?","Es una onza",NOCAMBIAR);
  //es carnivoro y tiene color leonado y franjas negras -> es un tigre
  A.conectar("es carnivoro","Es un tigre",NOCAMBIAR);

  A.conectar("es de color leonado?","Es un tigre",NOCAMBIAR);
  A.conectar("tiene franjas negras?","Es un tigre",NOCAMBIAR);
  //es un ungulado y es de color leonado y tiene manchas obscuras,patlas,cuello largo -> jirafa
  A.conectar("es ungulado","Es una jirafa",NOCAMBIAR);
  A.conectar("es de color leonado?","Es una jirafa",NOCAMBIAR);
  A.conectar("tiene manchas obscuras?","Es una jirafa",NOCAMBIAR);

  A.conectar("tiene patas largas?","Es una jirafa",NOCAMBIAR);
  A.conectar("tiene cuello largo?","Es una jirafa",NOCAMBIAR);
  //es ungulado,franjas negras,color blanco -> zebra
  A.conectar("es ungulado","Es una cebra",NOCAMBIAR);

  A.conectar("tiene franjas negras?","Es una cebra",NOCAMBIAR);

  A.conectar("es de color blanco?","Es una cebra",NOCAMBIAR);
  //ave,no vuela,patas largas,cuello largo,blanco y negro -> avestruz
  A.conectar("es ave","Es una avestruz",NOCAMBIAR);
  A.conectar("vuela?","Es una avestruz",CAMBIAR);
  A.conectar("tiene patas largas?","Es una avestruz",NOCAMBIAR);

  A.conectar("tiene cuello largo?","Es una avestruz",NOCAMBIAR);
  A.conectar("es de color blanco y negro?","Es una avestruz",NOCAMBIAR);
  //ave,no vuela,nada,blanco y negro
  A.conectar("es ave","Es un pinguino",NOCAMBIAR);
  A.conectar("vuela?","Es un pinguino",CAMBIAR);
  A.conectar("nada?","Es un pinguino",NOCAMBIAR);
  A.conectar("es de color blanco y negro?","Es un pinguino",NOCAMBIAR);
  //ave,vuela -> albatros
  A.conectar("es ave","Es un albatros",NOCAMBIAR);
  A.conectar("vuela?","Es un albatros",NOCAMBIAR);
  //Nuevas reglas mías para que funcione mejor
  //tiene pelo -> no tiene plumas

  A.pintar();
  A.te_adivino();
  return 0;
}
