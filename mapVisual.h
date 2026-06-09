#ifndef MAPVISUAL_H_
#define MAPVISUAL_H_

#include <iostream>
#include <string>
using namespace std;

class MapVisual{
    private:
        string unfoldedVisual;
        string chat[7];

        string user;
        string userState;

        char spriteRoles[3];
        char spriteStates[3];

    public:
        MapVisual();
        MapVisual(string username);

        void updateState(int row, int clm, int state);
        void updateRole(int row, int clm, int role);

        void chatState(string name, int state, int role);
        void chatRole(string name, int role);
        void chatPresence(int presence);
        void chatFalseExecution(int rw, int clm, int role);

        void updateUser(int karma, int sus);

        void death();
        void victory();
        
        void printMap();
};



// Definicion de constructor
MapVisual::MapVisual()
    :user("male07"), userState(""), unfoldedVisual(" n_ABCDEF\n 1_UUUUUU\n 2_UUUUUU\n 3_UUUUUU\n 4_UUUUUU\n 5_UUUUUU\n 6_UUUUUU"){
    
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

        for (int i = 0; i < 7; i++){
            chat[i] = "";
        }
    }


MapVisual::MapVisual(string username)
    :user(username),userState(""),unfoldedVisual(" n_ABCDEF\n 1_UUUUUU\n 2_UUUUUU\n 3_UUUUUU\n 4_UUUUUU\n 5_UUUUUU\n 6_UUUUUU"){
    
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

        for (int i = 0; i < 7; i++){
            chat[i] = "";
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



// Text
void MapVisual::chatState(string name, int state, int role){
    for (int i = 0; i <= 5; i++){
        chat[i] = chat[i+1];
    }
    chat[6] = name + " is ";
    if (state == 1){chat[6] = chat[6] + "alive.";}
    else if (state == 2){chat[6] = chat[6] + "going to fucking kill me help!!";}
    else if (state == 3){
        chat[6] = chat[6] + " dead, they were a ";
        chat[6] = chat[6] + spriteRoles[role - 1];
    }
}

void MapVisual::chatRole(string name, int role){
    for (int i = 0; i <= 5; i++){
        chat[i] = chat[i+1];
    }
    chat[6] = name + " is a ";
    chat[6] = chat[6] + spriteRoles[role - 1];
    chat[6] = chat[6] + "!";
}

void MapVisual::chatPresence(int presence){
    for (int i = 0; i <= 5; i++){
        chat[i] = chat[i+1];
    }

    if (presence == 0){chat[6] = "There are no traitors around...";}
    else if (presence == 1){chat[6] = "I feel a menacing presence... ";}
    else if (presence > 1){chat[6] = "They are everywhere! ";}
}

void MapVisual::chatFalseExecution(int rw, int clm, int role){
    for (int i = 0; i <= 5; i++){
        chat[i] = chat[i+1];
    }

    chat[6] ="This ";
    chat[6] = chat[6] + spriteRoles[role - 1];
    chat[6] = chat[6] + " is dead already";
}



void MapVisual::updateUser(int karma, int sus){
    string susLevel;
    if (sus <= 2){susLevel = "Reputable";}
    else if (sus <= 5){susLevel = "Liability";}
    else if (sus >= 6){susLevel = "KOS";}
    
    userState = "        "+ user + ": (" + susLevel + ")     Karma: " + (to_string(karma));
}


// printer
void MapVisual::printMap(){
    string mapPrint="";
    int chatIndex = 0;

    mapPrint.append(unfoldedVisual.substr(0, 9) + "       " + chat[chatIndex++]);
    for (int i = 9; i < unfoldedVisual.size(); i += 10){
       mapPrint.append(unfoldedVisual.substr(i, 10) + "       " + chat[chatIndex++]);
    }
    cout << mapPrint << "\n\n" << userState << endl;
}

#endif