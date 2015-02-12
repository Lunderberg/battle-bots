#include "Actor.hh"

Actor::Actor() : x(0), y(0) { }

Actor::~Actor(){}

void Actor::Act(){
  auto action = ChooseAction();
  switch(action.activity){
  case Activity::Wait:
    break;

  case Activity::Move:
    switch(action.direction){
    case Direction::North:
      y += 1;
      break;
    case Direction::South:
      y -= 1;
      break;
    case Direction::East:
      x += 1;
      break;
    case Direction::West:
      x -= 1;
      break;
    }
    break;

  case Activity::Attack:
    break;
  }
}
