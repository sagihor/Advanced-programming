#ifndef ENTITY_H
#define ENTITY_H
#include<iostream>
using namespace std;
class Entity
{
  char* _name;
  int _max_life;
  int _curr_life;
  int _damage;
  ostream& show(ostream& out) const;
  public:
    //constructors
    Entity(char* name=nullptr, int max_life, int damage, int curr_life);
    Entity(int max_life,int damage);
    Entity(const Entity& entity);
    Entity();
    //destructor
    ~Entity();
    //opertaors
    Entity& operator+=(int life_increament);
    Entity& operator-=(int damage_decreament);
    Entity& operator-=(const Entity& entity);
    bool operator==(const Entity& entity) const;
    bool operator>(const Entity& entity) const;
    friend ostream& operator<<(ostream& os, const Entity& entity);
};
#endif //ENTITY_H
