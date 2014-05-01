#include "GameAsset.h"
#include "Player.h"

#ifndef HEARTASSET_H_
#define HEARTASSET_H_

class HeartAsset : public GameAsset {
 public:
  HeartAsset();
  HeartAsset(float x, float y, float z);
    ~HeartAsset();

  bool collidesWith(Player & a);

  virtual void update();
  virtual void draw();
  virtual void clean();

  enum vertices {
	  F0, F1, F2, F3, F4, F5,
  };

};

#endif // HEARTASSET_H_
