/**
 * Traitor.h
 * Proyecto TC1030
 *
 * created by Jose Manuel Lemus Gomez - A01707194
 * 
 */

#ifndef TRAITOR_H_
#define TRAITOR_H_

#include "Entity.h"
#include <iostream>
using namespace std;

// Declaracion de clase Traitor que hereda de Entity
class Traitor: public Entity{
    private:
    // Atributos propios
    int aggroTolerance; // Límite de agresividad
    int aggroLevel; // Nivel actual de agresividad

    // Metodo auxiliares
    void increaseAggro();

    public:
    // Constructores
    Traitor();
    Traitor(string nm);

    // Metodos sobreescritos
    void damage(int dg) override;
    void unhide() override;

    // Metodos propios
    void notice();
    void appease();
};



//Definicion de constructores
Traitor::Traitor()
    :Entity(), aggroTolerance(1), aggroLevel(0){}

Traitor::Traitor(string nm)
    :Entity(2, false, nm, 1, 100), aggroTolerance(6), aggroLevel(0){}



// Definicion de métodos propios

/**
 * Incrementa el nivel de agresividad del traidor.
 * Si alcanza o supera la tolerancia establecida,
 * cambia su estado a Triggered.
 * param: ninguno
 * return
 */
void Traitor::increaseAggro(){
    aggroLevel = aggroLevel + 2;
    if (aggroLevel >= aggroTolerance){
        state = 2;
    } 
}

/**
 * Indica que el traidor detecto actividad del jugador.
 * Utiliza increaseAggro() para aumentar su agresividad.
 * param: ninguno
 * return
 */
void Traitor::notice(){
    increaseAggro();
}

void Traitor::appease(){
    aggroLevel = aggroLevel - 4;
    if (aggroLevel < 0){aggroLevel=0;}
}


// Definicion de metodos sobreescritos

/**
 * Reduce la vida de la entidad según el daño recibido.
 * Si la vida llega a cero o menos, el estado cambia a muerto.
 * aparte incrementa su nivel aggro.
 * param: int (daño)
 * return
 */
void Traitor::damage(int dg){
    health = health - dg;

    increaseAggro();
    
    if (health <= 0){
        state = 3;
    }
}

/**
 * Revela la identidad del traidor
 * Cambia su visibilidad a true y aumenta su nivel de aggro.
 * param: ninguno
 * return
 */
void Traitor::unhide(){
    visibility = true;
    increaseAggro();
}

#endif
