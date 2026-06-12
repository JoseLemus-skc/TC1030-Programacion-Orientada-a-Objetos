/**
 * Proyecto RDM - Garry's Mod TTT experience. 
 * Programacion Orientada a Objetos (TC1030)
 *
 * Jose Manuel Lemus Gomez - A01707194 
 * 
 * En este proyecto se desarrolla una adaptación simplificada del modo de juego
 * "Trouble in Terrorist Town" (TTT) de Garry's Mod. El jugador interactúa con
 * un tablero de coordenadas donde todos los otros "jugadores" son inicialmente
 * desconocidos y debe decidir entre inspeccionar o atacarlos.
 * 
 */

#include "entity.h"
#include "inno.h"
#include "traitor.h"
#include "detective.h"
#include "entityPool.h"
#include "mapVisual.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int DIMENSION = 6;
const int DIMENSIONSQR = DIMENSION*DIMENSION;

// Funciones de utilidad
/**
 *Funcion para limpiar visualmente la pantalla imprimiendo saltos de linea.
 *param: ninguno
 *return
 */
void cleanScreen(){
    cout << "\n\n\n\n\n\n\n\n\n\n\n\\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

/**
 *Funcion para pausar la ejecucion del programa y que explicimente
 *indique al usuario a escribir algo y presionar Enter
 *param> ninguno
 *return
 */
void waitForInputTutorial(){
    string temp;
    cout << "\nType and press enter: " << endl;
    cout << "> ";
    cin >> temp;
    return;
}

/**
 *Funcion para pausar la ejecucion del preograma hasta que
 *el usuario escriba algo y presione Enter
 *param
 *return
 */
void waitForInput(){
    string temp;
    cout << "\n> ";
    cin >> temp;
    return;
}

/**
 *Funcion que convierte una letra de columna a su indice numerico
 *param: char (clm)
 *return: int (-1 si es invalida)
 */
int coordinateColumn(char clm){
    char letters[6] = {'A','B','C','D','E','F'};
    for (int i = 0; i < 6; i++){
        if (clm == letters[i]){
            return i;
        }
    }
    return -1;
}

/**
 *Funcion que convierte el numero de fila a a un indice valido
 *param: int (rw)
 *return: int (-1 si es invalido)
 */
int coordinateRow(int rw){
    rw = rw - 1;
    if (rw < DIMENSION && rw >= 0){
        return rw;
    }
    else{return -1;}
}

/**
 *Funcion que procesa una coordenada ingresada por el usuario
 *y obtiene indices de fila y columna validos
 *param: string (coordinate), int referencia (rw), int referencia (clm)
 *return - Cambios directos a rw y clm
 */
void coordinateProcessing(string coordinate, int &rw, int &clm){
    rw = -1;
    clm = -1;
    
    if (coordinate.size() < 2 || coordinate.size() > 2){return;}
    
    char raw_clm = coordinate[0];
    clm = coordinateColumn(raw_clm);

    int raw_rw = stoi(coordinate.substr(1));
    rw = coordinateRow(raw_rw);
}

/**
 *Funcion que registra en un arreglo la informacion de cualquier objeto que
 *cambio de estado o visibilidad a lo largo de una ronda.
 *param: int (row), int (clm), int (vc) cambio de estado o visibilidad, arreglo 2D (storage), int referencia (index)
 *return - Cambios directos al index y al arreglo "Storage"
 */
void recordedChanges(int row, int clm, int vc, int storage[][3], int &index){
    if (index == DIMENSIONSQR){return;}
    storage[index][0] = row; // Fila
    storage[index][1] = clm; // Columna
    storage[index][2] = vc; // Cambio de estado o visibilidad
    
    index++;
}

// Funciones de Input 

/**
 *Funcion que muestra el tutorial del juego y explica su funcionamiento
 *param: ninguno
 *return
 */
void tutorial(){
    string temp;

    cout << "> ";
    cin >> temp;

    if (temp != "y"){return;}

    cleanScreen();
    cout << "Trouble in Terrorist Town (TTT) is a social deduction game.\nA few players are secretly Traitors and must eliminate everyone else.\nThe Innocents must discover who the Traitors are before it is too late." << endl;
    waitForInputTutorial();

    cleanScreen();
    cout << "Unfortunately, you suffer from a severe and rare visual impairment.\nEverybody looks like a single character on a coordinate grid." << endl;
    waitForInputTutorial();

    cleanScreen();
    MapVisual tutorialMap;
    tutorialMap.updateUser(100, 0);

    cout << "This is your screen:" << endl << endl;
    tutorialMap.printMap();

    cout << "\nCoordinates are written like A1, C4, or F6.\nColumns use letters, rows use numbers, if you needed it spelled out..." << endl;
    waitForInputTutorial();

    cleanScreen();
    cout << "Every symbol on the map means something:" << endl;
    cout << "? = Unknown player" << endl;
    cout << "# = Game over" << endl;
    cout << "X = Dead player" << endl;
    cout << "\n";
    cout << "When you identify a player, you may see:" << endl;
    cout << "I = Innocent" << endl;
    cout << "T = Traitor" << endl;
    cout << "D = Detective" << endl;
    waitForInput();

    cleanScreen();
    tutorialMap.printMap();

    cout << "\nActions:" << endl;
    cout << "1) Attack" << endl;
    cout << "   Shoot a player" << endl;
    cout << "2) Inspect" << endl;
    cout << "   Reveal a player (and get a whiff of any traitors around that player)" << endl;
    cout << "3) (Secret) Grenade" << endl;
    cout << "   Damage multiple nearby players at once." << endl;
    waitForInput();

    cleanScreen();
    cout << "Be careful.\nKilling innocent players lowers your Karma and makes you look suspicious.\nSuspicious players attract attention." << endl;
    waitForInput();

    cleanScreen();
    cout << "In regular TTT, killing random people without evidence is called RDM (Random Death Match).\nNormally this is considered bad.\nIn this game, however, you're basically blind.\nEveryone is a question mark.\nSo pray to whoever you pray to because this is all just a desperate attempt to RDM the correct people." << endl;
    waitForInput();

    cleanScreen();

    cout << "You lose if: Your Karma gets too low. Too many people suspect you. A traitor gets suspicious of you.\nYou dont win." << endl << endl;
    waitForInput();

    cleanScreen();
    cout << "it wasnt implemented..." << endl;
    waitForInput();

    cleanScreen();
    cout << "Welcome to RDM." << endl;
    waitForInput();
}

/**
 *Funcion para que el usuario ingrese la dificultad de la partida.
 *param: ninguno
 *return: int 
 */
int selectDifficulty(){
    int difficulty;

    do{
        cout << "Select difficulty:" << endl;
        cout << "(0) Easy" << endl;
        cout << "(1) Medium" << endl;
        cout << "(2) Hard" << endl;
        cout << "(3) Super Hard" << endl;
        cout << "> ";

        cin >> difficulty;

        if (difficulty < 0 || difficulty > 3){
            cout << "Invalid option." << endl;
        }

    } while (difficulty < 0 || difficulty > 3);

    return difficulty;
}

/**
 *Funcion para solicitar al usuario una coordenada y procesarla.
 *param: int referencia (rw), int referencia (clm).
 *return: - Cambios directos al rw y al arreglo clm
 */
void inputCoordinate(int &rw, int &clm){
    string coordinate;

    do{
        cout << "Insert a coordinate: " << endl;
        cout << ">  ";
        cin >> coordinate;

        coordinateProcessing(coordinate, rw, clm);

        if (rw == -1 || clm == -1){
            cout << "Invalid coordinate." << endl;
        }

    } while (rw == -1 || clm == -1);
}

/**
 *Funcion para solicitar al usuario una accion.
 *param: ninguno
 *return: int
 */
int inputAction(){
    int option;

    do{
        cout << "Choose an action:" << endl;
        cout << "(1) Attack" << endl;
        cout << "(2) Inspect" << endl;
        cout << "> ";
        cin >> option;

        if (option < 1 || option > 3){
            cout << "Invalid option." << endl;
        }

    } while (option < 1 || option > 3);

    return option;
}


// Funciones de Renderizado
/**
 *Funcion que actualiza el mapa visual con los cambios registrados durante la ronda.
 *param: MapVisual referencia (mapa), EntityPool (entities), arreglo 2D (storage), int (index)
 *return:
 */
void syncRenderedEntities(MapVisual &mapa, EntityPool &entities, int storage[][3], int index){
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

/**
 *Funcion que actualiza los datos del jugador mostrados en el mapa
 *param: MapVisual (mapa), int (susLevel), int (userKarma)
 *return
 */
void syncRenderedUI(MapVisual &mapa, int susLevel, int userKarma){
    mapa.updateUser(userKarma, susLevel);
}

/**
 *Funcion que actualiza el mapa sobre de presencia de traidores o inputs fallidos
 *param: int (rw), int (clm) EntityPool(entities), MapVisual (mapa), bool (executionFlag), int (pFlag)
 *return
 */
void syncRenderedFlags(int rw, int clm, EntityPool &entities, MapVisual &mapa, bool executionFlag, int pFlag){
    if (executionFlag == false){mapa.chatFalseExecution(rw, clm, entities.getEntity(rw, clm)->getRole());}
    if (pFlag >= 0){mapa.chatPresence(pFlag);}
}



// Funciones de gameplay (Reglas del juego)

/**
 *Funcion que verifica si se cumple alguna condicion de game over
 *param: EntityPool(entities), arreglo 2D (storage), int (index), bool (karmaCheck)
 *return: int
 */
int checkDeathLoss(EntityPool &entities, int storage[][3], int index, bool karmaCheck){
    for (int i = 0; i < index; i++){
        int tempRow = storage[i][0];
        int tempClm = storage[i][1];

        Entity* tempPtr = entities.getEntity(tempRow, tempClm);
        int tempState = tempPtr->getState();
        int tempRole = tempPtr->getRole();

        if (tempState == 2 && tempRole == 2){return 1;}
        else if ((tempState == 2 && tempRole == 3) && (karmaCheck == true)){return 2;}
    }
    return 0;
}

/**
 *Funcion que calcula el karma y los sus points que el usuario acumulo
 *durante la ronda y valida una condicion de game over.
 *param: int (karma), int (sus)
 *return: bool
 */
bool karmaCheck(int karma, int sus){
    if (karma < 70 && sus > 4){;return true;}
    return false;
}



// Funciones de gameplay (Interacciones con Entities)
/**
 *Funcion que alerta a las entidades dentro de un espacio 3*3 sobre el ataque de usuario a no Traitor.
 *param: int (rw), int (clm), int (sprd), const int (limits), EntityPool (entities), arreglo 2D (storage), int (index)
 *return: - Cambios directos a las entidades en EntityPool y el arreglo "Sotrage" e index.
 */
void areaAlertBetrayal(int rw, int clm, int sprd, const int &limits, EntityPool &entities, int storage[][3], int &index){

    for (int i = (rw - sprd); i <= (rw + sprd); i++){
        if (i < 0 || i >= limits){continue;}

        for (int j = (clm - sprd); j <= (clm + sprd); j++){
            if (j < 0 || j >= limits){continue;}
            else if (i == rw && j == clm){continue;}

            Entity* tempPtr = entities.getEntity(i, j);
            int state0 = tempPtr->getState();

            if (state0 != 3){
                if (tempPtr->getRole() == 3){
                Detective* tempDetective = dynamic_cast<Detective*>(tempPtr);

                tempDetective->increaseAggro();

                int statef = tempPtr->getState();
                if (state0 != statef){recordedChanges(i, j, 1, storage, index);}
                }
            
                else if (tempPtr->getRole() == 2){
                    Traitor* tempTraitor = dynamic_cast<Traitor*>(tempPtr);
                    tempTraitor->appease();
                }
            }
        }
    }
}

/**
 *Funcion que aplica daño a una entidad y registra algun cambio de estado (muerte) sin registrar el exito de la interaccion.
 *param: int (rw), int (clm), int (dmg), int (sprd), EntityPool (entities), const int (limit), arreglo 2D (storage), int (index)
 *return
 */
void attackEntity(int rw, int clm, int dmg, int sprd, EntityPool &entities, const int &limit, int storage[][3], int &index){
    Entity* tempPtr = entities.getEntity(rw, clm);
    
    int state0 = tempPtr->getState();
    int role = tempPtr->getRole();
    
    if (state0 != 3){
        tempPtr->damage(dmg);
        int statef = tempPtr->getState();

        if (state0 != statef){
            recordedChanges(rw, clm, 1, storage, index);
            if ((statef == 3) && (role != 2)){
                areaAlertBetrayal(rw, clm, sprd, limit, entities, storage, index);
            }
        }
    }
}

/**
 *Funcion que aplica daño a una entidad, registra algun cambio de estado e indica si la accion fue ejecutada con exito.
 *param: int (rw), int (clm), int (dmg), int (sprd), EntityPool (entities), const int (limit), arreglo 2D (storage), int (index), bool (execFlag)
 *return
 */
void attackEntity(int rw, int clm, int dmg, int sprd, EntityPool &entities, const int &limit, int storage[][3], int &index, bool &execFlag){
    Entity* tempPtr = entities.getEntity(rw, clm);

    int state0 = tempPtr->getState();
    int role = tempPtr->getRole();

    if (state0 != 3){
        tempPtr->damage(dmg);
        int statef = tempPtr->getState();

        if (state0 != statef){
            recordedChanges(rw, clm, 1, storage, index);
            if ((statef == 3) && (role != 2)){
                areaAlertBetrayal(rw, clm, sprd, limit, entities, storage, index);
            }
        }
        execFlag = true;
    }
    else{
        execFlag = false;
    }
}

/**
 *Funcion que ajusta el karma y nivel de sospecha que se tiene del jugador segun el tipo de entidad que ataco.
 *param: int (rw), int (clm), int (dmg), EntityPool (entities), int (sus), int (karma)
 *return
 */
void karmaPenalty(int rw, int clm, int dmg, EntityPool &entities, int &sus, int &karma){
    Entity* tempPtr = entities.getEntity(rw, clm);
    
    int state0 = tempPtr->getState();
    int role = tempPtr->getRole();
    
    if (state0 != 3){
        if (role == 1){
            sus = sus+(dmg/50);
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


/**
 *Funcion que revela una entidad y registra el cambio de visibilidad sin registrar el exito de la interaccion.
 *param: int (rw), int (clm), EntityPool (entities), arreglo 2D (storage), int (index)
 *return
 */
void unhideEntity(int rw, int clm, EntityPool &entities, int storage[][3], int &index){
    Entity* tempPtr = entities.getEntity(rw, clm);
    
    int state0 = tempPtr->getState();

    if (state0 != 3){
        bool vis0 = tempPtr->getVisibility();
        tempPtr->unhide();
        bool visf = tempPtr->getVisibility();
    
        if (vis0 != visf){recordedChanges(rw, clm, 0, storage, index);}
    }
}

/**
 *Funcion que revela una entidad, registra el cambio de visibilidad e indica si la accion fue ejecutada con exito.
 *param: int (rw), int (clm), EntityPool (entities), arreglo 2D (storage), int (index), bool (execFlag)
 *return
 */
void unhideEntity(int rw, int clm, EntityPool &entities, int storage[][3], int &index, bool &execFlag){
    Entity* tempPtr = entities.getEntity(rw, clm);
    
    int state0 = tempPtr->getState();

    if (state0 != 3){
        bool vis0 = tempPtr->getVisibility();
        tempPtr->unhide();
        bool visf = tempPtr->getVisibility();
    
        if (vis0 != visf){recordedChanges(rw, clm, 0, storage, index);}

        execFlag = true;
    }
    else{execFlag = false;}
}

/**
 *Funcion que alerta a un traidor de encontrarse dentro del rango de una inspeccion de area y registra cualquier cambio de estado.
 *param: int (rw), int (clm), EntityPool (entities), arreglo 2D (storage), int (index)
 *return
 */
void alertEntity(int rw, int clm, EntityPool &entities, int storage[][3], int &index){
    Entity* tempPtr = entities.getEntity(rw, clm);
    int state0 = tempPtr->getState();

    if (state0 != 3){
        Traitor* tempPtr_Traitor = dynamic_cast<Traitor*>(tempPtr);
        tempPtr_Traitor->notice();
        int statef = tempPtr->getState();
    
        if (state0 != statef){recordedChanges(rw, clm, 1, storage, index);}
    }
}



// Funciones de gameplay (Interacciones con multiples Entities)

/**
 *Funcion que recorre un area cuadrada alrededor de una coordenada y cuenta los traidores detectados.
 *param: int (rw), int (clm), int (sprd), const int (limits), EntityPool (entities), arreglo 2D (storage), int (index)
 *return: int
 */
int areaInspect(int rw, int clm, int sprd, const int &limits, EntityPool &entities, int storage[][3], int &index){
    int traitorCounter = 0;

    for (int i = (rw - sprd); i <= (rw + sprd); i++){
        if (i < 0 || i >= limits){continue;}

        for (int j = (clm - sprd); j <= (clm + sprd); j++){
            if (j < 0 || j >= limits){continue;}
            else if(i == rw && j == clm){continue;}

            Entity* tempPtr = entities.getEntity(i, j);
            if(tempPtr->getRole() == 2){

                alertEntity(i, j, entities, storage, index);

                traitorCounter++;
            }
        }
    }
    return traitorCounter;
}

/**
 *Funcion que recorre y dana a todas las entidades dentro de un area cuadrada alrededor de una coordenada.
 *param: int (rw), int (clm), int (sprd), int (dmg), const int (limits), EntityPool (entities), arreglo 2D (storage), int (index), int (sus), int (karma)
 *return
 */
void areaDamage(int rw, int clm, int sprd, int dmg, const int &limits, EntityPool &entities, int storage[][3], int &index, int &sus, int &karma){

    for (int i = (rw - sprd); i <= (rw + sprd); i++){
        if (i < 0 || i >= limits){continue;}

        for (int j = (clm - sprd); j <= (clm + sprd); j++){
            if (j < 0 || j >= limits){continue;}
            else if(i == rw && j == clm){continue;}

            karmaPenalty(i, j, dmg, entities, sus, karma);
            attackEntity(i, j, dmg, 1, entities, limits, storage, index);
        }
    }
}

/**
 *Funcion que recorre un perimetro en forma de cruz alrededor de una coordenada y cuenta los traidores detectados.
 *param: int (rw), int (clm), const int (limits), EntityPool (entities), arreglo 2D (storage), int (index)
 *return: int
 */
int crossInspect(int rw, int clm, const int &limits, EntityPool &entities, int storage[][3], int &index){
    int traitorCounter = 0;

    for (int i = rw - 1; i <= rw + 1; i++){
        if (i < 0 || i >= limits) continue;

        for (int j = clm - 1; j <= clm + 1; j++){
            if (j < 0 || j >= limits) continue;
            if (i == rw && j == clm) continue;
            if (i != rw && j != clm) continue;

            Entity* tempPtr = entities.getEntity(i, j);

            if (tempPtr->getRole() == 2){
                alertEntity(i, j, entities, storage, index);
                traitorCounter++;
            }
        }
    }
    return traitorCounter;
}

/**
 *Funcion que recorre un perimetro en forma de cruz alrededor de una coordenada y dana a todas las entidades dentro.
 *param: int (rw), int (clm), int (sprd), int (dmg), const int (limits), EntityPool (entities), arreglo 2D (storage), int (index), int (sus), int (karma)
 *return
 */
void crossDamage(int rw, int clm, int dmg, const int &limits, EntityPool &entities, int storage[][3], int &index, int &sus, int &karma){
for (int i = rw - 1; i <= rw + 1; i++){
        if (i < 0 || i >= limits) continue;

        for (int j = clm - 1; j <= clm + 1; j++){
            if (j < 0 || j >= limits) continue;
            if (i == rw && j == clm) continue;
            if (i != rw && j != clm) continue;


            karmaPenalty(i, j, dmg, entities, sus, karma);
            attackEntity(i, j, dmg, 1, entities, limits, storage, index);
        }
    }
}



// Funciones de gameplay (Manejo de rondas)
/**
 *Funcion que configura modificadores (area de areaDamage y multiplicadores de daño) deacorde a la dificultad seleccionada.
 *param: int (difficulty), float (multiplier), bool (useCross), int (inspectSpread)
 *return
 */
void difficultyMultiplier(int difficulty, float &multiplier, bool &useCross, int &inspectSpread){
    multiplier = 1.0;
    useCross = false;
    inspectSpread = 1;

    if (difficulty == 0){
        multiplier = 0.5;
        useCross = true;
    }
    else if (difficulty == 1){
        multiplier = 1;
        useCross = true;
    }
    else if (difficulty == 2){
        multiplier = 2;
        inspectSpread = 1;
    }
    else if (difficulty == 3){
        multiplier = 3;
        inspectSpread = 2;
    }
}

/**
 *Funcion que ejecuta una ronda completa del juego y regresa los resultados para continuar o concluir el juego.
 *param: int (susLevel), int (userKarma), MapVisual (mapa), EntityPool (entities), float (multiplier), bool (useCross), int (inspectSpread)
 *return: int
 */
int executeRound(int &susLevel, int &userKarma, MapVisual &mapa,EntityPool &entities, float multiplier, bool useCross, int inspectSpread){    
    mapa.printMap();

    int row, column, option, karmaResult;

    inputCoordinate(row, column);

    bool successFlag = true;
    int presenceFlag = -1;

    int stChanges = 0;
    int stChangesStorage[DIMENSIONSQR][3];

    option = inputAction();

    if (option == 1){
        karmaPenalty(row, column, 100 * multiplier, entities, susLevel, userKarma);
        attackEntity(row, column, 100, inspectSpread, entities, DIMENSION, stChangesStorage, stChanges, successFlag);
    }
    else if (option == 2){
        unhideEntity(row, column, entities, stChangesStorage, stChanges, successFlag);
        
        if (useCross == true){
            presenceFlag = crossInspect(row, column, DIMENSION, entities, stChangesStorage, stChanges);
        }
        else{
            presenceFlag = areaInspect(row, column, inspectSpread, DIMENSION, entities, stChangesStorage, stChanges);
        } 
    }
    else if (option == 3){
        karmaPenalty(row, column, 125 * multiplier, entities, susLevel, userKarma);
        attackEntity(row, column, 200, inspectSpread, entities, DIMENSION, stChangesStorage, stChanges, successFlag);

        if (useCross == true){
            crossDamage(row, column, 25 * multiplier, DIMENSION, entities, stChangesStorage, stChanges, susLevel, userKarma);
        }
        else{
            areaDamage(row, column, inspectSpread, 50 * multiplier, DIMENSION, entities, stChangesStorage, stChanges, susLevel, userKarma);
        }
    }

    syncRenderedFlags(row, column, entities, mapa, successFlag, presenceFlag);
    syncRenderedEntities(mapa, entities, stChangesStorage, stChanges);
    syncRenderedUI(mapa, susLevel, userKarma);

    karmaResult = karmaCheck(userKarma, susLevel);
    return (checkDeathLoss(entities, stChangesStorage, stChanges, karmaResult));
}


/**
 *Funcion principal que inicializa el mapa, el entituPool y ejecuta un ciclo completo del juego.
 *param: string (playerName), int (difficulty)
 *return
 */
void game(string playerName, int difficulty){

    char map1[DIMENSION][DIMENSION] = {
        {'T','T','I','I','I','I'},
        {'I','I','I','I','I','I'},
        {'I','I','I','T','I','I'},
        {'I','I','I','I','T','I'},
        {'I','I','T','I','I','I'},
        {'I','D','I','D','I','I'}
    };

    char map2[DIMENSION][DIMENSION] = {
        {'I','I','I','T','I','I'},
        {'I','I','I','I','I','I'},
        {'I','I','I','I','I','I'},
        {'I','I','I','I','T','I'},
        {'I','I','I','I','I','I'},
        {'I','D','I','I','I','I'}
    };

    char map3[DIMENSION][DIMENSION] = {
        {'T','I','I','I','I','T'},
        {'I','I','I','D','I','I'},
        {'I','I','I','I','I','I'},
        {'I','I','T','I','I','I'},
        {'I','D','I','I','I','I'},
        {'I','I','I','I','T','I'}
    };

    char map4[DIMENSION][DIMENSION] = {
        {'I','I','I','I','D','I'},
        {'I','I','T','I','I','I'},
        {'I','I','I','I','I','I'},
        {'I','D','I','I','I','I'},
        {'I','I','I','T','I','T'},
        {'I','I','I','I','I','T'}
    };

    char debug[DIMENSION][DIMENSION] = {
        {'I','I','I','I','I','I'},
        {'I','I','I','I','I','I'},
        {'I','I','D','I','I','I'},
        {'I','I','I','I','I','I'},
        {'I','I','I','I','I','I'},
        {'I','I','I','I','I','T'}
    };

    string namePool[DIMENSIONSQR] = {
        "StringBean", "simulacra", "gatita", "Somkey", "Trumbone_Jones", "OBagglietto",
        "DaintyLight", "MrTinRobot", "stubs", "monkeydog", "Driggs9DrillMine)", "BIG",
        "Sgt.Hartman", "lamp", "BlueSkys", "Ed", "scoooot", "sky",
        "tyrone", "Death", "Halloweenie", "AccroonGaming", "natybumbo", "glucose",
        "Mamulons1", "TaeGoingGirlmode", "kimmie", "Jerry", "SlurpUpUrButty", "mcLovin",
        "TheShowerBagel", "mordecaiMagico777", "RicuNav", "Darkness",
        "hoppipottla", "Anton"
    };

    float multiplier;
    bool useCross;
    int inspectSpread;

    difficultyMultiplier(difficulty, multiplier, useCross, inspectSpread);

    int sus = 0;
    int karma = 100;
    int gameOver = 0;

    EntityPool game;
    
    srand(time(0));
    int i = (rand() % 4) + 1;
    cout << "map: " << i;

    if (i == 1) {game.loadMap(map1, namePool);}
    if (i == 2){game.loadMap(map2, namePool);}
    if (i == 3) {game.loadMap(map3, namePool);}
    if (i == 4){game.loadMap(map4, namePool);}

    MapVisual gameMap(playerName);

    while (gameOver == 0){
        cleanScreen();
        gameOver = executeRound(sus, karma, gameMap, game, multiplier, useCross, inspectSpread);
    }

    cleanScreen();
    gameMap.printMap();
    waitForInputTutorial();

    cleanScreen();
    if(gameOver == 2){gameMap.deathKarma();}
    else if (gameOver == 1){gameMap.deathKilled();}
}


// Main
int main(){

    string playerName;
    bool replay;
    char option;

    cout << "Insert a username " << endl;
    cout << "> ";
    cin >> playerName;

    cout << "\nDo you wish to read the intro? (y/n)" << endl;
    tutorial();

    do{
        cleanScreen();

        int difficulty = selectDifficulty();

        game(playerName, difficulty);

        cout << "\nPlay again? (y/n): ";
        cin >> option;

        if (option == 'n'){replay = false;} 
        else {replay = true;} 
    } while (replay == true);
    return 0;
}
