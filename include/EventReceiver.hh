#ifndef _EVENTRECEIVER_H_
#define _EVENTRECEIVER_H_

#include <irrlicht.h>

struct SMouse{
  SMouse() : x(0), y(0) {}
  int x,y;
};

class EventReceiver : public irr::IEventReceiver{
public:
  EventReceiver();

  virtual bool OnEvent(const irr::SEvent& event);

  bool IsKeyDown(irr::EKEY_CODE keyCode) const {
    return KeyIsDown[keyCode];
  }

  SMouse mouse() const {
    return MouseInfo;
  }

  float GetMouseWheel() const { return wheel; }
  void ResetMouseWheel(){ wheel = 0; }

private:
  bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
  SMouse MouseInfo;
  float wheel;
};

#endif /* _EVENTRECEIVER_H_ */
