#include "CubeAsset.h"
#include "IInterpolator.h"

#ifndef FLOORASSET_H_
#define FLOORASSET_H_

class FloorAsset : public GameAsset {
 public:
  FloorAsset();
  FloorAsset(float x, float y, float z);
    ~FloorAsset();

  virtual void update();
  virtual void draw();
  void setInterpolator(shared_ptr<IInterpolator> li);
 private:
  shared_ptr<IInterpolator> li;
};

#endif // FLOORASSET_H_
