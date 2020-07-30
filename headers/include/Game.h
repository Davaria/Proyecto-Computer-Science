#ifndef GAME_H 
#define GAME_H 

#include "SFML/Audio.hpp"
#include "../../src/Character.cpp"
#include "./Entity.h"
#include "../../src/Terrain.cpp"
#include <vector>

using namespace std;

class Game
{
  RenderWindow window;
  Texture texBackground;
  Sprite spBackground;

  Music bgm;
  int c=0;

  // Personaje y enemigos
  Character *character;
  Enemy *enemy;
  // Vector de punteros , invocar poliformicamente update, draw
  vector<Entity * > entities;
  // tamaño definido 
  int height = 576;
  int width = 324;

  //Test de Terreno
  Terrain *ground;

  void init();
  void update();
  void draw();

public:
  Game();
  void run();
  void add(Entity *);
  // ~Game();
};

#endif