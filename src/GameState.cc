#include "GameState.hh"

#include <cstdlib>
#include <iostream>

GameState::GameState(int width, int height) :
  width(width), height(height) {
  for(int i=0; i<width; i++){
    for(int j=0; j<height; j++){
      if(i+j < 15){
        map.push_back(Tile::Stone);
      } else {
        map.push_back(Tile::Dirt);
      }
    }
  }
}

void GameState::FrameUpdate(){
  for(auto& actor : actors){
    UpdateActor(actor);
  }
}

Tile GameState::GetTileAt(int x, int y) const {
  if(x>=0 && x<width &&
     y>=0 && y<height){
    return map.at(y*width + x);
  } else {
    return Tile::OutOfBounds;
  }
}

void GameState::AddActor(std::unique_ptr<Actor> actor){
  actor->SetGameState(this);
  actors.push_back(std::move(actor));
}

void GameState::UpdateActor(std::shared_ptr<Actor> actor){
  auto action = actor->ChooseAction();

  switch(action.activity){
  case Activity::Wait:
    break;

  case Activity::Move:
    switch(action.direction){
    case Direction::North:
      actor->SetY(actor->GetY() + 1);
      break;
    case Direction::South:
      actor->SetY(actor->GetY() - 1);
      break;
    case Direction::East:
      actor->SetX(actor->GetX() + 1);
      break;
    case Direction::West:
      actor->SetX(actor->GetX() - 1);
      break;
    }
    break;
  }
}
