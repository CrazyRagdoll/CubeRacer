#include "GameAsset.h"

#ifndef Bullet_H_
#define Bullet_H_

class Bullet : public GameAsset {
 public:
  Bullet();
  Bullet(float x, float y, float z);
  ~Bullet();

  virtual void update();
  virtual void draw();
  virtual void clean();

};

#endif // Bullet_H_
