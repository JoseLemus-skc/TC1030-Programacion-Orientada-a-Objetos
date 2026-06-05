#ifndef TRAITOR_H_
#define TRAITOR_H_

#include "entity.h"
#include <iostream>
using namespace std;

class Traitor: public Entity{
    private:
    int aggroTolerance; // Constante
    int aggroLevel;

    void increaseAggro();

    public:
    Traitor();
    Traitor(string nm);

    void damage(int dg) override;
    void unhide() override;
};



//Definicion de constructores
Traitor::Traitor()
    :Entity(), aggroTolerance(1), aggroLevel(0){}

Traitor::Traitor(string nm)
    :Entity(2, false, nm, 1, 100), aggroTolerance(10), aggroLevel(0){}



// Definicion de metodos propios
void Traitor::increaseAggro(){
    aggroLevel = aggroLevel + 5;
    if (aggroLevel >= aggroTolerance){
        state = 2;
    } 
}



// Definicion de metodos sobreescritos
void Traitor::damage(int dg){
    health = health - dg;

    increaseAggro();
    
    if (health <= 0){
        state = 3;
    }
}

void Traitor::unhide(){
    visibility = true;

    increaseAggro();
}

#endif