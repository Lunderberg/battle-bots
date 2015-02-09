#include "Actor.hh"

Actor::Actor() : x(0), y(0) { }

Actor::~Actor(){}

void Actor::Act(){
  switch(ChooseAction()){
  case Action::Wait:
    break;

  case Action::MoveLeft:
    x -= 1;
    break;
  case Action::MoveRight:
    x += 1;
    break;
  case Action::MoveUp:
    y += 1;
    break;
  case Action::MoveDown:
    y -= 1;
    break;

  case Action::AttackLeft:
    break;
  case Action::AttackRight:
    break;
  case Action::AttackUp:
    break;
  case Action::AttackDown:
    break;
  }
}
