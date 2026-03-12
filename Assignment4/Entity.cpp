
#include "Entity.h"

#include <string.h>

Entity::Entity(char* name, int max_life, int damage, int curr_life)
    :_max_life(max_life) ,_damage(damage), _curr_life(curr_life){
  char* temp = new char[strlen(name) + 1];
  strcpy(temp, name);
  _name = temp;
}

Entity::Entity(int max_life, int damage) :_name(nullptr), _curr_life(_max_life)
,_damage(damage), _max_life(max_life){
}
Entity::Entity():_name(nullptr), _max_life(0), _damage(0), _curr_life(0) {

}
Entity::Entity(const Entity& other){
  this->_name = (char*)malloc(strlen(other._name) + 1);
  if (this->_name == NULL){
    printf("Memory allocation error\n");
  }
  this->_name = strcpy(this->_name, other._name);
  this->_max_life = other._max_life;
  this->_damage = other._damage;
}
Entity& Entity::operator+=(int life_increament){
  this->_max_life = this->_max_life + life_increament;
  return *this;
}
Entity& Entity::operator-=(const Entity& other){
  this->_max_life = this->_max_life - other._damage;
  return *this;
}
Entity& Entity::operator-=(int life_decreament){
  this->_max_life = this->_max_life - life_decreament;
  return *this;
}
bool Entity::operator==(const Entity& other)const{
  return this->_damage*this->_max_life == other._damage*other._max_life;
}
bool Entity::operator>(const Entity& other)const{
  return this->_damage*this->_max_life > other._damage*other._max_life;
}
ostream& Entity::show(ostream &out)const{
  out << "name" << this->_name << "(" << this->_curr_life << "/" << this->_max_life
      << ") - " << this->_damage <<endl;
}
ostream& operator<<(ostream& out, const Entity& entity){
  return entity.show(out);
}