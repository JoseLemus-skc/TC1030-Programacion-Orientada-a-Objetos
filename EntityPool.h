/**
 * EntityPool.h
 * Proyecto TC1030
 *
 * created by Jose Manuel Lemus Gomez - A01707194
 * 
 */

#ifndef ENTITYPOOL_H_
#define ENTITYPOOL_H_

#include "Entity.h"
#include "Inno.h"
#include "Traitor.h"
#include "Detective.h"

#include <iostream>
using namespace std;

// Declaracion de clase EntityPool
class EntityPool{
    private:
    // Atributos
    Entity* eDistribution[6][6]; // Matriz de apuntadores a entidades

    public:
    // Constructor
    EntityPool();
    // Destructor
    ~EntityPool();

    // Metodos
    void loadMap(char distributionMap[6][6], string namePool[36]);

    Entity* getEntity(int row, int clm);
};



// Definicion de constructor

/**
 * Constructor por defecto.
 * Inicializa todas las posiciones de la matriz con nullpointers.
 * param: ninguno
 * return
 */
EntityPool::EntityPool(){
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 6; j++){
                eDistribution[i][j] = nullptr;
        }
    }
}

// Definicion de destructor
/**
 * Destructor.
 * Libera el espacio de las posiciones de la matriz y las rellena con nullpointers.
 * param: ninguno
 * return
 */
EntityPool::~EntityPool(){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++){
            delete eDistribution[i][j];
            eDistribution[i][j] = nullptr;
        }
    }
}

// Definiciones de metodos

/**
 * Uso de composicion
 * Carga una matriz de distribución tipo "mapa".
 * Dependiendo del carácter recibido crea un Traitor, Detective o Inno
 * en el heap y almacena un apuntador en la posición correspondiente.
 * param: matriz char[6][6] y arreglo string[36]
 * return
 */
void EntityPool::loadMap(char distributionMap[6][6], string namePool[36]){
    int npIndex = 0;
    
    for (int i = 0; i < 6; i++){
            for (int j = 0; j < 6; j++){
                if (distributionMap[i][j] == 'T'){
                    eDistribution[i][j] = new Traitor(namePool[npIndex]);
                }
                else if (distributionMap[i][j] == 'D'){
                    eDistribution[i][j] = new Detective(namePool[npIndex]);
                }
                else{
                    eDistribution[i][j] = new Inno(namePool[npIndex]);
                }

                npIndex++;
        }
    }
}


/**
 * Regresa el apuntador a la entidad almacenada
 * en la coordenada especificada.
 * param: int (fila), int (columna)
 * return: Entity*
 */
Entity* EntityPool::getEntity(int row, int clm){
    return eDistribution[row][clm];
}

#endif
