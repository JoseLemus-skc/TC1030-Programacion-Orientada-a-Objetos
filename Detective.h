/**
 * Detective.h
 * Proyecto TC1030
 *
 * created by Jose Manuel Lemus Gomez - A01707194
 * 
 */

#ifndef DETECTIVE_H_
#define DETECTIVE_H_

#include "Entity.h"
#include <iostream>
using namespace std;

// Declaracion de clase Detective que hereda de Entity
class Detective: public Entity{
    private:
    // Atributos propios
    int aggroLevel; // Límite de agresividad
    int aggroTolerance; // Nivel actual de agresividad
    
    public:
    // Constructores
    Detective();
    Detective(string nm);

    // Metodos sobreescritos
    void damage(int dg) override;
    void unhide() override;
    
    // Metodo propio
    void increaseAggro();
};



//Definicion de constructores
Detective::Detective()
    :Entity(), aggroTolerance(1), aggroLevel(0){}

Detective::Detective(string nm)
    :Entity(3, false, nm, 1, 150), aggroTolerance(10), aggroLevel(0){}



// Definicion de metodos propios

/**
 * Incrementa el nivel de agresividad del traidor.
 * Si alcanza o supera la tolerancia establecida,
 * cambia su estado a Triggered.
 * param: ninguno
 * return
 */
void Detective::increaseAggro(){
    aggroLevel = aggroLevel + 5;
    if (aggroLevel >= aggroTolerance){
        state = 2;
    } 
}



// Definicion de metodos sobreescritos

/**
 * Reduce la vida de la entidad según el daño recibido.
 * Si la vida llega a cero o menos, el estado cambia a muerto.
 * aparte incrementa su nivel aggro.
 * param: int daño
 * return
 */
void Detective::damage(int dg){
    health = health - dg;

    increaseAggro();
    
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
void Detective::unhide(){
    visibility = true;
}

#endif