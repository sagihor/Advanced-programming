//
// Created by sagih on 24/01/2025.
//

#ifndef GAME_H
#define GAME_H
using namespace std;
#include "Entity.h"
#include "Room.h"
class Game {
    Entity _player;
    Room* _start_room;
  const std::string& configFile;;
  public:
    Game(const Entity &player, const std::string &configFile);
    void assign_rooms(const Room& room);
    ~Game();
};



#endif //GAME_H
