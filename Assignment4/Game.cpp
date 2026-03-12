#include "Game.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
static int _CURRENT_ROOM = 0;
using namespace std;

Game::Game(const Entity &player, const std::string& configFile) : _player(player), _start_room(),
                                                                  configFile() {
    ifstream config(configFile);
    for (string line; getline(config, line);) {
        char* room_id;
        int life_increase;
        int life_mon;
        int damage_mon;
        istringstream stream(line);

        // Read the room_id and skip the leading space
        string temp;
        getline(stream, temp, ' ');  // Read room_id part (before space)

        // Remove any leading zeroes (if necessary)
        temp = temp.substr(temp.find_first_not_of('0'));  // Trim leading zeroes, if any

        // Allocate memory for room_id and copy the value
        room_id = new char[temp.length() + 1];
        std::strcpy(room_id, temp.c_str());
        stream >> life_increase >> life_mon >> damage_mon;
        Room room = Room(life_increase, life_mon, damage_mon);

    }

}

void Game::assign_rooms(const Room &room) {
    char* temp = room.get_room_number();
    for (int i = strlen(temp); i > 0; i--) {
        _start_room[temp[i]];
    }
}

Game::~Game() {
}
