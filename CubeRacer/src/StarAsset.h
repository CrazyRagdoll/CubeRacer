#include "GameAsset.h"
#include "Player.h"

#ifndef StarASSET_H_
#define StarASSET_H_

class StarAsset : public GameAsset {
 public:
  StarAsset();
  StarAsset(float x, float y, float z);
    ~StarAsset();

  bool collidesWith(Player & a);

  virtual void update();
  virtual void draw();
  virtual void clean();

  enum vertices {
	  F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, 
  };

};

#endif // StarASSET_H_
