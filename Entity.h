/**
 * Entity.h
 * Proyecto TC1030
 *
 * created by Jose Manuel Lemus Gomez - A01707194
 * 
 */


#ifndef ENTITY_H_
#define ENTITY_H_

#include <iostream>
using namespace std;

// Declaracion de clase abstracta Entity
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

        // Metodos
        int getRole();
        bool getVisibility();
        string getName();
        int getState();
        int getHealth();
        
        // Metodos abstractos
        virtual void damage(int dg) = 0;
        virtual void unhide() = 0;
};



//Definicion de constructores
Entity::Entity()
    :role(0), visibility(false), name(""), state(0), health(1){}

Entity::Entity(int rl, bool vs, string nm, int st, int hl)
    :role(rl), visibility(vs), name(nm), state(st), health(hl){}



// Definicion de getters
/**
 * Regresa el rol de la entidad.
 * param: ninguno
 * return: int
 */
int Entity::getRole(){
    return role;
}

/**
 * Regresa el estado de visibilidad de la entidad.
 * param: ninguno
 * return: bool
 */
bool Entity::getVisibility(){
    return visibility;
}

/**
 * Regresa el nombre de la entidad.
 * param: ninguno
 * return: string
 */
string Entity::getName(){
    return name;
}

/**
 * Regresa el estado actual de la entidad.
 * param: ninguno
 * return: int
 */
int Entity::getState(){
    return state;
}

/**
 * Regresa la cantidad de vida de la entidad.
 * param: ninguno
 * return: int
 */
int Entity::getHealth(){
    return health;
}

#endif