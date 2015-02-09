#include "EventReceiver.hh"

#include <iostream>

EventReceiver::EventReceiver() : wheel(0) {
  for(irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; i++){
    KeyIsDown[i] = false;
  }
}

bool EventReceiver::OnEvent(const irr::SEvent& event){
  if(event.EventType == irr::EET_KEY_INPUT_EVENT){
    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  } else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
    switch(event.MouseInput.Event){

    case irr::EMIE_MOUSE_MOVED:
      MouseInfo.x = event.MouseInput.X;
      MouseInfo.y = event.MouseInput.Y;
      break;

    case irr::EMIE_MOUSE_WHEEL:
      wheel += event.MouseInput.Wheel;
      break;

    default:
      break;
    }
  }
  return false;
}
