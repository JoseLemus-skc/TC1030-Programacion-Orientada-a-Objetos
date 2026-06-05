#ifndef INNO_H_
#define INNO_H_

#include "entity.h"
#include <iostream>
using namespace std;

class Inno: public Entity{
    public:
    Inno();
    Inno(string nm);

    // Setters 
   void damage(int dg) override;
   void unhide() override;
};



//Definicion de constructores
Inno::Inno()
    :Entity(){}

Inno::Inno(string nm)
    :Entity(1, false, nm, 1, 50){}

// Definicion de setters
void Inno::damage(int dg){
    health = health - dg;
    if (health <= 0){
        state = 3;
    }
}

void Inno::unhide(){
    visibility = true;
}

#endif