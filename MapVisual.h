/**
 * mapVisual.h
 * Proyecto TC1030
 *
 * created by Jose Manuel Lemus Gomez - A01707194
 * 
 */

#ifndef MAPVISUAL_H_
#define MAPVISUAL_H_

#include <iostream>
#include <string>
using namespace std;

// Declaracion de clase MapVisual
class MapVisual{
    private:
        // Atributos
        string unfoldedVisual;
        string chat[7];

        string user;
        string userState;

        char spriteRoles[3];
        char spriteStates[3];

        // Metodos auxiliares
        void chatDeath();
        void chatKarmaDeath();

    public:
        // Constructores
        MapVisual();
        MapVisual(string username);

        // Metodos de sincronizacion de personajes
        void updateState(int row, int clm, int state);
        void updateRole(int row, int clm, int role);

        // Metodos de interfaz de usuario
        void chatState(string name, int state, int role);
        void chatRole(string name, int role);
        void chatPresence(int presence);
        void chatFalseExecution(int rw, int clm, int role);

        void updateUser(int karma, int sus);

        // Metodos de renderizaci[on
        void deathKarma();
        void deathKilled();
        void printMap();
};



// Definicion de constructores

/**
 * Constructor por defecto.
 * Inicializa el mapa visual, los sprites de roles, estados y el registro de mensajes del chat.
 * param: ninguno
 * return
 */
MapVisual::MapVisual()
    :user("male07"), userState(""), unfoldedVisual(" n_ABCDEF\n 1_UUUUUU\n 2_UUUUUU\n 3_UUUUUU\n 4_UUUUUU\n 5_UUUUUU\n 6_UUUUUU"){
    
        spriteRoles[0] = 'I';
        spriteRoles[1] = 'T';
        spriteRoles[2] = 'D';

        spriteStates[0] = '?'; // unknown
        spriteStates[1] = '#'; // about to kill you
        spriteStates[2] = 'X'; // Dead

        for (int i = 0; i < unfoldedVisual.size(); i++){
            if (unfoldedVisual[i] == 'U'){
                unfoldedVisual[i] = spriteStates[0];
            }
        }

        for (int i = 0; i < 7; i++){
            chat[i] = "";
        }
    }

/**
 * Constructor con parametro.
 * Inicializa el mapa visual utilizando un nombre del usuario.
 * param: string (username)
 * return
 */
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



// Definicion de metodos de sincronizacion de personajes

/**
 * Actualiza el simbolo del estado de una entidad.
 * param: int (row), int (column), int (estado)
 * return
 */
void MapVisual::updateState(int row, int clm, int state){
    int internalCoordinate =  ((row + 1) * 10) + (clm + 3);
    if (unfoldedVisual[internalCoordinate] != '\n'){
        unfoldedVisual[internalCoordinate] = spriteStates[state - 1];
    }
}

/**
 * Actualiza el simbolo correspondiente al rol de una entidad.
 * param: int (row), int (column), int (rol)
 * return
 */
void MapVisual::updateRole(int row, int clm, int role){
    int internalCoordinate =  ((row + 1) * 10) + (clm + 3);
    if (unfoldedVisual[internalCoordinate] != '\n'){
        unfoldedVisual[internalCoordinate] = spriteRoles[role - 1];
    }
    else{
        cout << "failed" << endl;
    }
}


// Definicion de metodos de interfaz de usuario

/**
 * Agrega al chat informacion sobre el estado actual de una entidad.
 * param: string (nombre), int (estado), int (rol)
 * return
 */
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

/**
 * Agrega al chat informacion sobre el rol de una entidad.
 * param: string (nombre), int (role)
 * return
 */
void MapVisual::chatRole(string name, int role){
    for (int i = 0; i <= 5; i++){
        chat[i] = chat[i+1];
    }
    chat[6] = name + " is a ";
    chat[6] = chat[6] + spriteRoles[role - 1];
    chat[6] = chat[6] + "!";
}

/**
 * Agrega al chat una pista sobre la cantidad de traidores en una ubicacion.
 * param: int (cantidad de traidores)
 * return
 */
void MapVisual::chatPresence(int presence){
    for (int i = 0; i <= 5; i++){
        chat[i] = chat[i+1];
    }

    if (presence == 0){chat[6] = "There are no traitors around...";}
    else if (presence == 1){chat[6] = "I feel a menacing presence... ";}
    else if (presence > 1){chat[6] = "They are everywhere! ";}
}

/**
 * Agrega al chat que se intento interactuar con una entidad que ya estaba muerta.
 * param: int (fila), int (columna), int (rol)
 * return
 */
void MapVisual::chatFalseExecution(int rw, int clm, int role){
    for (int i = 0; i <= 5; i++){
        chat[i] = chat[i+1];
    }

    chat[6] ="This ";
    chat[6] = chat[6] + spriteRoles[role - 1];
    chat[6] = chat[6] + " is dead already";
}


/**
 * Agrega al chat el mensaje de fin de ronda por falta de karma/sus points.
 * param: ninguno
 * return
 */
void MapVisual::chatKarmaDeath(){
    for (int i = 0; i <= 5; i++){
        chat[i] = chat[i+1];
    }

    chat[6] = user + " was killed by the detectives...";
}

/**
 * Agrega al chat el mensaje de fin de ronda por muerte del jugador.
 * param: ninguno
 * return
 */
void MapVisual::chatDeath(){
    for (int i = 0; i <= 5; i++){
        chat[i] = chat[i+1];
    }

    chat[6] = user + " was killed by a traitor...";
}

/**
 * Actualiza el karma y nivel de sospecha del jugador.
 * param: int (karma), int (pts sospecha)
 * return
 */
void MapVisual::updateUser(int karma, int sus){
    string susLevel;
    if (sus <= 2){susLevel = "Reputable";}
    else if (sus <= 5){susLevel = "Liability";}
    else if (sus >= 6){susLevel = "KOS";}
    
    userState = "        "+ user + ": (" + susLevel + ")     Karma: " + (to_string(karma));
}


// Definicion de metodos de renderizacion

/**
 * Imprime el mapa, el historial del chat y el estado actual del usuario.
 * param: ninguno
 * return
 */
void MapVisual::printMap(){
    string mapPrint="";
    int chatIndex = 0;

    mapPrint.append(unfoldedVisual.substr(0, 9) + "       " + chat[chatIndex++]);
    for (int i = 9; i < unfoldedVisual.size(); i += 10){
       mapPrint.append(unfoldedVisual.substr(i, 10) + "       " + chat[chatIndex++]);
    }
    cout << mapPrint << "\n\n" << userState << endl;
}

/**
 * Muestra una pantalla de muerte y genera el mensaje correspondiente al karma en el chat.
 * param: ninguno
 * return
 */
void MapVisual::deathKarma(){
    unfoldedVisual = " XXXXXXXX\n XXXXXXXX\n XXXXXXXX\n X-DEAD-X\n XXXXXXXX\n XXXXXXXX\n XXXXXXXX";
    chatKarmaDeath();

    string mapPrint="";
    int chatIndex = 0;

    mapPrint.append(unfoldedVisual.substr(0, 69) + "       " + chat[chatIndex++]);
    for (int i = 9; i < unfoldedVisual.size(); i += 10){
       mapPrint.append(unfoldedVisual.substr(i, 10) + "       " + chat[chatIndex++]);
    }
    cout << mapPrint << "\n\n" << userState << endl;
}

/**
 * Muestra una pantalla de muerte y genera el mensaje correspondiente a la merute del usuario en el chat.
 * param: ninguno
 * return
 */
void MapVisual::deathKilled(){
    unfoldedVisual = " XXXXXXXX\n XXXXXXXX\n XXXXXXXX\n X-DEAD-X\n XXXXXXXX\n XXXXXXXX\n XXXXXXXX";
    chatDeath();

    string mapPrint="";
    int chatIndex = 0;

    mapPrint.append(unfoldedVisual.substr(0, 9) + "       " + chat[chatIndex++]);
    for (int i = 9; i < unfoldedVisual.size(); i += 10){
       mapPrint.append(unfoldedVisual.substr(i, 10) + "       " + chat[chatIndex++]);
    }
    cout << mapPrint << "\n\n" << userState << endl;
}

#endif
