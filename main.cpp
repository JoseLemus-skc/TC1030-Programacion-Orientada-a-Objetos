#include "entity.h"
#include "inno.h"
#include "traitor.h"
#include "detective.h"
#include "entityPool.h"
#include "mapVisual.h"

#include <iostream>
using namespace std;

const int DIMENSION = 6;
const int DIMENSIONSQR = DIMENSION*DIMENSION;

// Funciones de utilidad
void cleanScreen(){
    cout << "\n\n\n\n\n\n\n\n\n\n\n\\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void pause(){
    string temp;
    cin >> temp;
    return;
}

int coordinateColumn(char clm){
    char letters[6] = {'A','B','C','D','E','F'};
    for (int i = 0; i < 6; i++){
        if (clm == letters[i]){
            return i;
        }
    }
    return 0;
}

void coordinateRow(int &row){
    row = row - 1;
    return;
}

void storeChangedCoordinates(int row, int clm, int vc, int storage[][3], int &index){
    if (index == DIMENSIONSQR){return;}
    storage[index][0] = row; // Fila
    storage[index][1] = clm; // Columna
    storage[index][2] = vc; // Cambio de estado o visibilidad
    
    index++;
}



// Tutorial
void tutorial(){
    string temp;
    char temp_char_input;
    int temp_char;
    int temp_int;
    cin >> temp;
    if (temp == "no"){
        return;
    }
    
    cleanScreen();
    cout << "Trouble in Terrorist Town (TTT) is a multiplayer gamemode included with Garrys Mod. Set in a parody of the Counter-Strike universe, the game\nis about a group of 'terrorists' who have traitors among them, out to kill everyone whos not a traitor." << endl;
    pause();

    cleanScreen();
    cout << "When the game starts, a small number of players is selected as Traitors, who have to kill all the Innocent players (ie. the rest of the players).\nThe Innocent players know they are in the majority, but they do not know who is a Traitor and who is not." << endl;
    pause();

    cleanScreen();
    cout<< "You are an innocent... You have to kill ALL traitors!" << endl;
    pause();

    cleanScreen();
    cout<< "You suffer from a severe visual disorder that turns the other players into simple characters in a coordinate field.\nLike this:" << endl;
    MapVisual tutorialMap;
    tutorialMap.printMap();
    pause();

    cleanScreen();
    cout<< "Thankfully you can inspect any of these characters to know if they are a traitor or an innocent like you.\nItll keep you from making any rash decisions that might make the detectives think YOU are a traitor." << endl;
    tutorialMap.printMap();
    pause();
    cout<< "Go ahead and enter a coordinate, like this: A3\nColumn: " ;
    cin >> temp_char_input;
    temp_char = coordinateColumn(temp_char_input);
    cout<< "position: " << temp_char;
    cout<< "row: ";
    cin >> temp_int;;
    coordinateRow(temp_int);

    cleanScreen();
    tutorialMap.printMap();
    cout<< "Now type 2 to simply inspect: ";
    pause();
    
    cleanScreen();
    tutorialMap.updateRole(temp_int, temp_char, 3);
    cout<< "A wild detective appears!" << endl;
    tutorialMap.printMap();
    pause();

    temp = 1;
    while (temp != "2"){
        cleanScreen();
        tutorialMap.printMap();
        cout<< "Now type 2 to kill him ";
        cin >> temp;
    }

    tutorialMap.updateState(temp_int, temp_char, 3);

    cleanScreen();
    cout<< "He is now dead... " << endl;
    tutorialMap.printMap();
    pause();

    cleanScreen();
    cout<< "And his buddies realized... " << endl;
    tutorialMap.updateState(0, 0, 2);
    tutorialMap.updateState(0, 4, 2);
    tutorialMap.updateState(3, 3, 2);
    tutorialMap.updateState(3, 4, 2);
    tutorialMap.updateState(5, 2, 2);
    tutorialMap.updateState(2, 1, 2);
    tutorialMap.updateState(2, 2, 2);
    tutorialMap.updateState(2, 4, 2);
    tutorialMap.printMap();
    cout<< "oops... ";
    pause();

    cleanScreen();
    tutorialMap.death();
    pause();
    cout << "This is what happens when you put down the wrong person..." << endl;
    pause();

    cleanScreen();
    cout << "Random Death Match (RDM) occurs when a player kills or attempts to kill another player for no apparent reason." << endl;
    cout << "Unfortunately you cant do anythung but! -blind and uncapable of doing nothing more but to guess..." << endl;
    pause();
    cout << "Welcome to 'RDM" << endl;
    cout << "Start Game?  ";
    pause();
    return;
}


// Renderizado
void updateChanges(MapVisual &mapa, EntityPool &entities, int storage[][3], int index){
    for (int i = 0; i < index; i++){
        int tempRow = storage[i][0];
        int tempClm = storage[i][1];
        int tempRole;
        int tempState;

        Entity* tempPtr = entities.getEntity(tempRow, tempClm);
        tempRole = tempPtr->getRole();
        tempState = tempPtr->getState();

        if (storage[i][2] == 0){
            mapa.updateRole(tempRow, tempClm, tempRole);
            mapa.chatRole(tempPtr->getName(),tempRole);
        }
        else if(storage[i][2] == 1){
            mapa.updateState(tempRow, tempClm, tempState);
            mapa.chatState(tempPtr->getName(),tempState, tempRole);
        }
    }
}

void updateUI(MapVisual &mapa, int susLevel, int userKarma){
    mapa.updateUser(userKarma, susLevel);
}

void updateFlags(int rw, int clm, EntityPool &entities, MapVisual &mapa, bool executionFlag, int pFlag){
    if (executionFlag == false){mapa.chatFalseExecution(rw, clm, entities.getEntity(rw, clm)->getRole());}
    if (pFlag >= 0){mapa.chatPresence(pFlag); cout << " YES" << endl;}
}

// Funciones de gameplay
bool endConditions1(EntityPool &entities, int storage[][3], int index){
    for (int i = 0; i < index; i++){
        int tempRow = storage[i][0];
        int tempClm = storage[i][1];

        Entity* tempPtr = entities.getEntity(tempRow, tempClm);
        int tempState = tempPtr->getState();

        if (tempState == 2){return true;}
    }
    return false;
}

bool endConditions2(int karma, int sus){
    if (karma < 700 && sus > 7){return true;}
    return false;
}

// Interacciones
void attackEntity(int rw, int clm, int dmg, EntityPool &entities, int storage[][3], int &index){
    Entity* tempPtr = entities.getEntity(rw, clm);
    
    int state0 = tempPtr->getState();
    
    if (state0 != 3){
        tempPtr->damage(dmg);
        int statef = tempPtr->getState();

        if (state0 != statef){storeChangedCoordinates(rw, clm, 1, storage, index);}
    }
}

void attackEntity(int rw, int clm, int dmg, EntityPool &entities, int storage[][3], int &index, bool &execFlag){
    Entity* tempPtr = entities.getEntity(rw, clm);
    
    int state0 = tempPtr->getState();
    
    if (state0 != 3){
        tempPtr->damage(dmg);
        int statef = tempPtr->getState();

        if (state0 != statef){storeChangedCoordinates(rw, clm, 1, storage, index);}

        execFlag = true;
    }
    else{execFlag = false;}
}

void karmaPenalty(int rw, int clm, int dmg, EntityPool &entities, int &sus, int &karma){
    Entity* tempPtr = entities.getEntity(rw, clm);
    
    int state0 = tempPtr->getState();
    int role = tempPtr->getRole();
    
    if (state0 != 3){
        if (role == 1){
            sus = sus+(dmg/10);
            karma = karma-(dmg/5);
        }
        else if (role == 2){
            sus = sus-(dmg/10);
            karma = karma+(dmg/2);
        }
        else if (role == 3){
            sus = sus+(dmg/5);
            karma = karma-(dmg/2);
        }
        if (sus < 0){sus = 0;}
    }
}

void unhideEntity(int rw, int clm, EntityPool &entities, int storage[][3], int &index, int sus, int karma){
    Entity* tempPtr = entities.getEntity(rw, clm);
    
    int state0 = tempPtr->getState();

    if (state0 != 3){
        bool vis0 = tempPtr->getVisibility();
        tempPtr->unhide();
        bool visf = tempPtr->getVisibility();
    
        if (vis0 != visf){storeChangedCoordinates(rw, clm, 0, storage, index);}
    }
}

void unhideEntity(int rw, int clm, EntityPool &entities, int storage[][3], int &index, bool &execFlag){
    Entity* tempPtr = entities.getEntity(rw, clm);
    
    int state0 = tempPtr->getState();

    if (state0 != 3){
        bool vis0 = tempPtr->getVisibility();
        tempPtr->unhide();
        bool visf = tempPtr->getVisibility();
    
        if (vis0 != visf){storeChangedCoordinates(rw, clm, 0, storage, index);}

        execFlag = true;
    }
    else{execFlag = false;}
}

void noticeEntity(int rw, int clm, EntityPool &entities, int storage[][3], int &index){
    Entity* tempPtr = entities.getEntity(rw, clm);
    int state0 = tempPtr->getState();

    if (state0 != 3){
        Traitor* tempPtr_Traitor = dynamic_cast<Traitor*>(tempPtr);
        tempPtr_Traitor->notice();
        int statef = tempPtr->getState();
    
        if (state0 != statef){storeChangedCoordinates(rw, clm, 1, storage, index);}
    }
}

// Interacciones Splash
int observeSpread(int rw, int clm, int sprd, const int &limits, EntityPool &entities, int storage[][3], int &index){
    int traitorCounter = 0;

    for (int i = (rw - sprd); i <= (rw + sprd); i++){
        if (i < 0 || i >= limits){continue;}

        for (int j = (clm - sprd); j <= (clm + sprd); j++){
            if (j < 0 || j >= limits){continue;}
            else if(i == rw && j == clm){continue;}

            Entity* tempPtr = entities.getEntity(i, j);
            if(tempPtr->getRole() == 2){

                noticeEntity(i, j, entities, storage, index);

                traitorCounter++;
            }
        }
    }
    return traitorCounter;
}

void damageSpread(int rw, int clm, int sprd, int dmg, const int &limits, EntityPool &entities, int storage[][3], int &index, int &sus, int &karma){

    for (int i = (rw - sprd); i <= (rw + sprd); i++){
        if (i < 0 || i >= limits){continue;}

        for (int j = (clm - sprd); j <= (clm + sprd); j++){
            if (j < 0 || j >= limits){continue;}
            else if(i == rw && j == clm){continue;}

            attackEntity(i, j, dmg, entities, storage, index);
            karmaPenalty(i, j, dmg, entities, sus, karma);
        }
    }
}

// Ronda
bool round(int &susLevel, int &userKarma, MapVisual &mapa,EntityPool &entities){    
    mapa.printMap();

    bool isGameOver = false;
    char input_column = 'A';
    int column = 0;
    int row = 0;
    int option = 0;

    bool successFlag = true;
    int presenceFlag = -1;

    int stChanges = 0;
    int stChangesStorage[DIMENSIONSQR][3];

    cout << "Insert a column: ";
    cin >> input_column;
    column = coordinateColumn(input_column);
    cout << "Insert a row: ";
    cin >> row;
    coordinateRow(row);

    cout << "Choose an action: (1) Attack, (2) Inspect." << endl;
    cin >> option;

    if (option == 1){
        karmaPenalty(row, column, 100, entities, susLevel, userKarma);
        attackEntity(row, column, 100, entities, stChangesStorage, stChanges, successFlag);
    }
    else if (option == 2){
        unhideEntity(row, column, entities, stChangesStorage, stChanges, successFlag);
        presenceFlag = observeSpread(row, column, 1, DIMENSION, entities, stChangesStorage, stChanges);
    }
    else{
        cout << "Invalid option.";
        pause();
        return false;
    }

    updateChanges(mapa, entities, stChangesStorage, stChanges);
    updateFlags(row, column, entities, mapa, successFlag, presenceFlag);
    updateUI(mapa, susLevel, userKarma);

    return (endConditions1(entities, stChangesStorage, stChanges) || endConditions2(userKarma, susLevel) );
}


int main(){  

    // Declaracion de variables (arreglos)
    char map1[DIMENSION][DIMENSION] = {
        {'T','T','I','I','I', 'I'},
        {'I','I','I','I','I', 'I'},
        {'I','I','I','I','I', 'I'},
        {'I','I','I','I','T', 'I'},
        {'I','I','I','I','I', 'I'},
        {'I','D','I','D','I', 'I'},
    };

    string namePool[DIMENSIONSQR] = {"StringBean", "simulacra", "gatita", "Somkey", "Trumbone_Jones", "OBagglietto", "DaintyLight", "MrTinRobot", 
                        "stubs", "monkeydog", "Driggs9DrillMine)", "BIG", "Sgt.Hartman", "lamp", "BlueSkys", "Ed", "scoooot", "sky",
                        "tyrone", "Death", "Halloweenie", "AccroonGaming", "natybumbo", "glucose", "Mamulons1", "TaeGoingGirlmode",
                        "kimmie", "Jerry", "SlurpUpUrButty", "mcLovin", "TheShowerBagel", "mordecaiMagico777", "RicuNav", "Darkness", 
                        "hoppipottla", "Anton"};


    // Declaracion de variables
    string playerName;
    int sus =0;
    int karma = 100;
    bool gameOver = false;

    // Inicio
    cout << "Insert a username: ";
    cin >> playerName;

    // Tutorial
    cout << "Do you wish to read the intro? Type 'yes' or 'no'" << endl;
    tutorial();
    cleanScreen();

    // Inicializacion del juego
    EntityPool game;
    game.loadMap(map1,namePool);
    MapVisual gameMap(playerName);
    
    // Loop de turnos

    while(gameOver == false){
        cleanScreen();
        gameOver = round(sus, karma, gameMap, game);
    }
    gameMap.printMap();
    pause();

    gameMap.death();
}
