#ifndef ROOM_H
#define ROOM_H
#include<iostream>

#include "Entity.h"
using namespace std;
class Room
    {
    char* _room_number;
    int _life_increment;
    Entity _monster;
    Room* accessible_rooms[10]{};
  public:
    Room(int life_increment = 0, int life_monster = 0, int damage_monster = 0, char *room_number= nullptr);
    ~Room();
    //[] for access
    const Room* operator[](int index) const;
    //[] for assignment
    Room*operator[](int index);
    char* get_room_number() const;
    Room& operator=(const Room& room);
    bool operator<(const Room& room) const;
    };
#endif //ROOM_H
