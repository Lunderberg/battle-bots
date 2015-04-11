#include "GameState.hh"

#include <cstdlib>
#include <iostream>

GameState::GameState(int width, int height) :
  width(width), height(height) {
  for(int i=0; i<width; i++){
    for(int j=0; j<height; j++){
      //map.push_back(static_cast<Tile>(rand()%4));
      if(i+j < 5){
        map.push_back(Tile::Empty);
      } else if (i+j < 15){
        map.push_back(Tile::Dirt);
      } else {
        map.push_back(Tile::Stone);
      }
    }
  }
}

void GameState::FrameUpdate(){
  for(auto& actor : actors){
    UpdateActor(*actor);
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

GameStateView GameState::GetTileView(int x, int y) const {
  GameStateView output;

  for(int xview = x-10; xview<x+10; xview++){
    for(int yview = y-10; yview<y+10; yview++){
      int dist2 = (xview - x)*(xview - x) + (yview - y)*(yview - y);
      if(dist2 < 75){
        output.tiles.push_back({xview, yview, GetTileAt(xview,yview)});

        for(const auto& actor : actors){
          if(actor->GetX() == xview && actor->GetY() == yview){
            output.actors.push_back({xview, yview, actor->GetColor()});
          }
        }
      }
    }
  }

  return output;
}

GameStateView GameState::GetTileView() const {
  GameStateView output;

  int x = 0;
  int y = 0;
  for(auto tile : map){
    output.tiles.push_back({x,y,tile});

    x++;
    y += x/width;
    x %= width;
  }

  for(const auto& actor : actors){
    output.actors.push_back({actor->GetX(), actor->GetY(), actor->GetColor()});
  }

  return output;
}

void GameState::SetTileAt(Tile tile, int x, int y){
  if(x>=0 && x<width &&
     y>=0 && y<height){
    map.at(y*width + x) = tile;
  }
}

bool GameState::IsTileEmpty(int x, int y) const {
  if(GetTileAt(x,y) != Tile::Empty){
    return false;
  }
  for(const auto& actor : actors){
    if(actor->GetX() == x && actor->GetY() == y){
      return false;
    }
  }
  return true;
}

void GameState::AddActor(std::shared_ptr<Actor> actor){
  actor->SetGameState(this);
  actors.push_back(actor);
}

void GameState::UpdateActor(Actor& actor){
  auto action = actor.ChooseAction();

  // Track how long the actor has been working on the current job.
  if(action != actor.GetPreviousAction()){
    actor.SetTaskProgress(0);
  }
  actor.SetTaskProgress(actor.GetTaskProgress() + 100);

  int target_x, target_y;
  switch(action.direction){
  case Direction::North:
    target_x = actor.GetX();
    target_y = actor.GetY() + 1;
    break;
  case Direction::South:
    target_x = actor.GetX();
    target_y = actor.GetY() - 1;
    break;
  case Direction::East:
    target_x = actor.GetX() + 1;
    target_y = actor.GetY();
    break;
  case Direction::West:
    target_x = actor.GetX() - 1;
    target_y = actor.GetY();
    break;
  case Direction::Self:
    target_x = actor.GetX();
    target_y = actor.GetY();
    break;
  }

  switch(action.activity){
  case Activity::Wait:
    ActorWait(actor);
    break;
  case Activity::Move:
    ActorMove(actor, target_x, target_y);
    break;
  case Activity::Attack:
    ActorAttack(actor, target_x, target_y);
    break;
  }

  actor.SetPreviousAction(action);
}

void GameState::ActorMove(Actor& actor, int target_x, int target_y){
  if(IsTileEmpty(target_x, target_y)){
    actor.SetX(target_x);
    actor.SetY(target_y);
  }
}

void GameState::ActorWait(Actor& actor){ }

void GameState::ActorAttack(Actor& actor, int target_x, int target_y){
  if((GetTileAt(target_x, target_y) == Tile::Dirt) &&
     (actor.GetTaskProgress() >= 400)){
    SetTileAt(Tile::Empty, target_x, target_y);
    actor.SetTaskProgress(0);
  }
  if((GetTileAt(target_x, target_y) == Tile::Stone) &&
     (actor.GetTaskProgress() >= 3000)){
    SetTileAt(Tile::Dirt, target_x, target_y);
    actor.SetTaskProgress(0);
  }
}
