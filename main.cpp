#include "entity.h"
#include "inno.h"
#include "traitor.h"
#include "detective.h"
#include "entityPool.h"
#include "mapVisual.h"

#include <iostream>
using namespace std;

int main(){  
    // Declaracion de funciones
    void tutorial();
    void cleanScreen();
    void coordinateColumn(char &clm);
    void coordinateRow(int &row);

    // Declaracion de variables (arreglos)
    char map1[6][6] = {
        {'T','I','I','I','I', 'I'},
        {'I','I','I','I','I', 'I'},
        {'I','I','I','I','I', 'I'},
        {'I','I','I','I','T', 'I'},
        {'I','I','I','I','I', 'I'},
        {'I','D','I','D','I', 'I'},
    };

    string namePool[36] = {"StringBean", "simulacra", "gatita", "Somkey", "Trumbone_Jones", "OBagglietto", "DaintyLight", "MrTinRobot", 
                        "stubs", "monkeydog", "Driggs9DrillMine)", "BIG", "Sgt.Hartman", "lamp", "BlueSkys", "Ed", "scoooot", "sky",
                        "tyrone", "Death", "Halloweenie", "AccroonGaming", "natybumbo", "glucose", "Mamulons1", "TaeGoingGirlmode",
                        "kimmie", "Jerry", "SlurpUpUrButty", "mcLovin", "TheShowerBagel", "mordecaiMagico777", "RicuNav", "Darkness", 
                        "hoppipottla", "Anton"};


    // Declaracion de variables
    string playerName;
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
    MapVisual gameMap;
    
    // Loop de turnos
    while(gameOver == false){
        // Inicializacion de variables por turno
        char column = 0;
        int row = 0;
        int option = 0;
        int state0 = 0;
        int statef = 0;
        int role = 0;
        
        gameMap.printMap();

        cout << "Insert a column: ";
        cin >> column;
        coordinateColumn(column);
        cout << "Insert a row: ";
        cin >> row;
        coordinateRow(row);


        role = game.getEntity(row, column)->getRole();

        cout << "Choose an action: (1) Attack, (2) Inspect." << endl;
        cin >> option;

        if (option == 1 && state0 != 3){
            game.getEntity(row, column)->damage(50);
        }
        else if (option == 2 && state0 != 3){
            game.getEntity(row, column)->unhide();
        }
        else if (state0 == 3){
            cout << "Its already dead.";
            cin >> option;
            continue;
        }
        else{
            cout << "Invalid option.";
            cin >> option;
            continue;
        }

        statef = game.getEntity(row, column)->getState();

        if(state0 != statef){
            gameMap.updateState(row, column, statef);
        }
        continue;
    }
}


// Funciones de utilidad
void cleanScreen(){
    cout << "\n\n\n\n\n\n\n\n\n\n\n\\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void pause(){
    string temp;
    cin >> temp;
    return;
}

void coordinateColumn(char &clm){
    char letters[6] = {'A','B','C','D','E','F'};
    for (int i = 0; i < 6; i++){
        if (clm == letters[i]){
            clm = i;
            return;
        }
    }
    return;
}

void coordinateRow(int &row){
    row = row - 1;
    return;
}

// Tutorial
void tutorial(){
    string temp;
    char temp_char;
    int temp_int;
    cin >> temp;
    if (temp == "no"){
        return;
    }
    
    cleanScreen();
    cout << "Trouble in Terrorist Town (TTT) is a multiplayer gamemode included with Garrys Mod. Set in a parody of the Counter-Strike universe, the game\nis about a group of 'terrorists' who have traitors among them, out to kill everyone whos not a traitor." << endl;
    cin >> temp;

    cleanScreen();
    cout << "When the game starts, a small number of players is selected as Traitors, who have to kill all the Innocent players (ie. the rest of the players).\nThe Innocent players know they are in the majority, but they do not know who is a Traitor and who is not." << endl;
    cin >> temp;

    cleanScreen();
    cout<< "You are an innocent... You have to kill ALL traitors!" << endl;
    cin >> temp;

    cleanScreen();
    cout<< "You suffer from a severe visual disorder that turns the other players into simple characters in a coordinate field.\nLike this:" << endl;
    MapVisual tutorialMap;
    tutorialMap.printMap();
    cin >> temp;

    cleanScreen();
    cout<< "Thankfully you can inspect any of these characters to know if they are a traitor or an innocent like you.\nItll keep you from making any rash decisions that might make the detectives think YOU are a traitor." << endl;
    tutorialMap.printMap();
    cin >> temp;
    cout<< "Go ahead and enter a coordinate, like this: A3\nColumn: " ;
    cin >> temp_char;
    coordinateColumn(temp_char);
    cout<< "row: ";
    cin >> temp_int;;
    coordinateRow(temp_int);

    cleanScreen();
    tutorialMap.printMap();
    cout<< "Now type 2 to simply inspect: ";
    cin >> temp;
    
    cleanScreen();
    tutorialMap.updateRole(temp_int, temp_char, 3);
    cout<< "A wild detective appears!" << endl;
    tutorialMap.printMap();
    cin >> temp;

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
    cin >> temp;

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
    cin >> temp;

    cleanScreen();
    tutorialMap.death();
    cin >> temp;
    cout << "This is what happens when you put down the wrong person..." << endl;
    cin >> temp;

    cleanScreen();
    cout << "Random Death Match (RDM) occurs when a player kills or attempts to kill another player for no apparent reason." << endl;
    cout << "Unfortunately you cant do anythung but! -blind and uncapable of doing nothing more but to guess..." << endl;
    cin >> temp;
    cout << "Welcome to 'RDM" << endl;
    cout << "Start Game?  ";
    cin >> temp;
    return;
}



