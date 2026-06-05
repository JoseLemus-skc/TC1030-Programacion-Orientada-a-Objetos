#ifndef MAPVISUAL_H_
#define MAPVISUAL_H_

#include <iostream>
using namespace std;

class MapVisual{
    private:
        string unfoldedVisual;

        char spriteRoles[3];
        char spriteStates[3];

    public:
        MapVisual();

        void updateState(int row, int clm, int state);
        void updateRole(int row, int clm, int role);

        void death();
        void victory();
        
        void printMap();
};



// Definicion de constructor
MapVisual::MapVisual()
    :unfoldedVisual(" n_ABCDEF\n 1_UUUUUU\n 2_UUUUUU\n 3_UUUUUU\n 4_UUUUUU\n 5_UUUUUU\n 6_UUUUUU"){
    
        spriteRoles[0] = 'I';
        spriteRoles[1] = 'T';
        spriteRoles[2] = 'D';

        spriteStates[0] = '?';
        spriteStates[1] = '#';
        spriteStates[2] = 'X';

        for (int i = 0; i < unfoldedVisual.size(); i++){
            if (unfoldedVisual[i] == 'U'){
                unfoldedVisual[i] = spriteStates[0];
            }
        }
}



// Definicion de updaters
void MapVisual::updateState(int row, int clm, int state){
    int internalCoordinate =  ((row + 1) * 10) + (clm + 3);
    if (unfoldedVisual[internalCoordinate] != '\n'){
        unfoldedVisual[internalCoordinate] = spriteStates[state - 1];
    }
}

void MapVisual::updateRole(int row, int clm, int role){
    int internalCoordinate =  ((row + 1) * 10) + (clm + 3);
    if (unfoldedVisual[internalCoordinate] != '\n'){
        unfoldedVisual[internalCoordinate] = spriteRoles[role - 1];
    }
    else{
        cout << "failed" << endl;
    }
}


// Screens
void MapVisual::death(){
    cout <<"__UUUU__\nXXXXXXXX\nX-DEAD-X\nXXXXXXXX\nUUUUUUUU\nUUUUUUUU" << endl;
}

void MapVisual::victory(){
    cout <<"n_ABCDEF\n1_UUUUUU\n:3____:3\nv YAY! V\n:3____:3\n5_UUUUUU\n6_UUUUUU" << endl;
}


// printer
void MapVisual::printMap(){
    cout << unfoldedVisual << endl;
}

#endif