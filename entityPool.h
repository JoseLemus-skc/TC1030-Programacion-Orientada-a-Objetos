#ifndef ENTITYPOOL_H_
#define ENTITYPOOL_H_

#include "entity.h"
#include "inno.h"
#include "traitor.h"
#include "detective.h"

#include <iostream>
using namespace std;

class EntityPool{
    private:
    Entity* eDistribution[6][6];

    public:
    EntityPool(); // Poner un destructor

    void loadMap(char distributionMap[6][6], string namePool[36]);

    Entity* getEntity(int row, int clm);
};



// Definicion de constructor
EntityPool::EntityPool(){
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 6; j++){
                eDistribution[i][j] = nullptr;
        }
    }
}

// Definicion de setter
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



// Definicion de getter
Entity* EntityPool::getEntity(int row, int clm){
    return eDistribution[row][clm];
}

#endif