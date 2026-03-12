#include "Room.h"
#include <string.h>
using namespace std;
Room::Room(int life_increment, int life_monster, int damage_monster, char* room_number)
    : _life_increment(life_increment), _monster(life_monster, damage_monster){
    for (int i = 0; i < 10; i++) {
        this->accessible_rooms[i] = nullptr;
    }
    char* room_name = new char[strlen(room_number) + 1];
    strcpy(room_name, room_number);
    _room_number = room_name;
}

Room::~Room() {
}

const Room* Room::operator[](int index) const {
    if (index < 0 || index >= _life_increment) {
        std::cout << "Room index out of bounds" << std::endl;
    }
    else {
        return accessible_rooms[index];
    }
    return nullptr;
}

Room* Room::operator[](int index) {
    if (index < 0 || index >= _life_increment) {
        std::cout << "Room index out of bounds" << std::endl;
    }
    else {
        return accessible_rooms[index];
    }
    return nullptr;
}

char * Room::get_room_number() const {
    return _room_number;
}

Room & Room::operator=(const Room &room) {
    if (this != &room) {
        _life_increment = room._life_increment;
        _monster = room._monster;
        _room_number = room._room_number;
        for (int i = 0; i < 10; i++) {
            this->accessible_rooms[i] = room.accessible_rooms[i];
        }
    }
    return *this;
}

bool Room::operator<(const Room &room) const {
    return stoi(_room_number) < stoi(room._room_number);
}
