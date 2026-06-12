/**
 * Inno.h
 * Proyecto TC1030
 *
 * created by Jose Manuel Lemus Gomez - A01707194
 * 
 */

#ifndef INNO_H_
#define INNO_H_

#include "Entity.h"
#include <iostream>
using namespace std;

// Declaracion de clase Inno que hereda de Entity
class Inno: public Entity{
    public:
    // Constructores
    Inno();
    Inno(string nm);

   // Métodos sobrescritos
   void damage(int dg) override;
   void unhide() override;
};



//Definicion de constructores
Inno::Inno()
    :Entity(){}

Inno::Inno(string nm)
    :Entity(1, false, nm, 1, 50){}



// Definicion de metodos sobreescritos
/**
 * Reduce la vida de la entidad según el daño recibido.
 * Si la vida llega a cero o menos, el estado cambia a muerto.
 * param: int daño
 * return
 */
void Inno::damage(int dg){
    health = health - dg;
    if (health <= 0){
        state = 3;
    }
}

/**
 * Revela la identidad del inocente.
 * Cambia su visibilidad a true.
 * param: ninguno
 * return
 */
void Inno::unhide(){
    visibility = true;
}

#endif