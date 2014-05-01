#include "GameAsset.h"
#include "IInterpolator.h"

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
  void setInterpolator(shared_ptr<IInterpolator> li);

 private:
  shared_ptr<IInterpolator> li;
};

#endif // Bullet_H_
