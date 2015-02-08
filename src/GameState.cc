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

Tile GameState::GetTileAt(int i, int j) const {
  if(i>=0 && i<width &&
     j>=0 && j<height){
    return map.at(j*width + i);
  } else {
    return Tile::OutOfBounds;
  }
}
