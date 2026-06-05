#ifndef DETECTIVE_H_
#define DETECTIVE_H_

#include "entity.h"
#include <iostream>
using namespace std;

class Detective: public Entity{
    private:
    int aggroLevel;
    int aggroTolerance;
    
    public:
    Detective();
    Detective(string nm);

    void damage(int dg) override;
    void unhide() override;
    
    void increaseAggro();
};



//Definicion de constructores
Detective::Detective()
    :Entity(), aggroTolerance(1), aggroLevel(0){}

Detective::Detective(string nm)
    :Entity(3, false, nm, 1, 100), aggroTolerance(10), aggroLevel(0){}



// Definicion de metodos propios
void Detective::increaseAggro(){
    aggroLevel = aggroLevel + 5;
    if (aggroLevel >= aggroTolerance){
        state = 2;
    } 
}



// Definicion de metodos sobreescritos
void Detective::damage(int dg){
    health = health - dg;

    increaseAggro();
    
    if (health <= 0){
        state = 3;
    }
}

void Detective::unhide(){
    visibility = true;
}

#endif