TC1030-Programacion-Orientada-a-Objetos

# RDM. - Juego tipo BattleShip basado en Garrys Mod.
Este proyecto se basa al rededor del modo de juego Trouble in Terrorist Town (TTT) incluido en Garry's Mod. El juego en sí trata sobre un grupo de terroristas (hence Terrorist Town) que tienen traidores entre sus filas, cuyo objetivo es matar a todos los que no sean traidores. Los jugadores Inocentes saben que son mayoría, pero no saben quién es un Traidor y quién no.

## Funcionalidad
En esta adaptación, los demás jugadores son representados como caracteres inmóviles dentro de un campo de coordenadas de 6x6. Inicialmente todas las entidades son desconocidas para el usuario. Durante cada ronda, el jugador puede interactuar con cualquier coordenada mediante dos acciones principales: inspeccionar o atacar. Al inspeccionar una coordenada se revela información sobre la entidad ubicada en ella y se puede detectar la presencia de Traidores en las celdas cercanas. Por otro lado, al atacar una coordenada se inflige daño a la entidad correspondiente. Además, existe una acción secreta que permite realizar daño en area, afectando múltiples entidades alrededor de una posición determinada.

El jugador también cuenta con dos atributos: karma y nivel de sospecha. Ambos cambian dependiendo de las decisiones tomadas durante la partida. Atacar Inocentes o Detectives disminuye el karma e incrementa la sospecha, mientras que atacar Traidores produce el efecto contrario. Si el jugador acumula demasiada sospecha junto con un karma bajo, y/o llama la atención de ciertos personajes, la partida termina.

El programa se construyó utilizando seis clases principales: La clase Entity funciona como clase base y representa cualquier personaje presente en el juegp. A partir de ella heredan las clases Inno, Traitor y Detective, cada una con comportamientos específicos relacionados con su rol dentro del juego. La clase EntityPool se encarga de crear, almacecar y controlar los accesos hacia todas las entidades presentes en el mapa, mientras que la clase MapVisual controla la representación visual del juegp y la información mostrada al jugador.

## Consideraciones
El programa funciona unicamente en la consola y fue desarrollado utilizando librerias C++ standar.

compilar con: g++ Entity.h Inno.h Traitor.h Detective.h EntityPool.h MapVisual.h main.cpp  -o rdm
