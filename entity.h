#ifndef ENTITY_H_
#define ENTITY_H_

#include <iostream>
using namespace std;

// Declaracion de clase

class Entity{
    protected:
        // Attributos
        int role; // 1 = Innocent, 2 = Traitor, 3 = Detective
        bool visibility;
        string name;
        int state; // 1 = Alive, 2 = Triggered, 3 = Dead
        int health;

    public:
        // Constructores
        Entity();
        Entity(int rl, bool vs, string nm, int st, int hl);

        // Getters
        int getRole();
        bool getVisibility();
        string getName();
        int getState();
        int getHealth();
        
        // Setters y Abstraccion de la clase
        virtual void damage(int dg) = 0;
        virtual void unhide() = 0;
};



//Definicion de constructores
Entity::Entity()
    :role(0), visibility(false), name(""), state(0), health(1){}

Entity::Entity(int rl, bool vs, string nm, int st, int hl)
    :role(rl), visibility(vs), name(nm), state(st), health(hl){}



// Definicion de getters
int Entity::getRole(){
    return role;
}

bool Entity::getVisibility(){
    return visibility;
}

string Entity::getName(){
    return name;
}

int Entity::getState(){
    return state;
}

int Entity::getHealth(){
    return health;
}

#endif