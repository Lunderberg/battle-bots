#ifndef _ACTOR_H_
#define _ACTOR_H_

class Actor{
public:
  virtual ~Action();
  virtual Action act() = 0;
};

#endif /* _ACTOR_H_ */
