#include "CubeAsset.h"
#include <SDL2/SDL.h>

#ifndef PLAYER_H_
#define PLAYER_H_

class Player : public GameAsset {
 public:
  Player();
  Player(float x, float y, float z);
    ~Player();;

  //Score
  virtual void incScore(double points);

  //Movement
  virtual void move(double moving);

  //Ammo
  virtual double getAmmo();
  virtual double getAmmoRate();
  virtual void changeAmmo(int ammoVal);

  //Vunrability
  virtual void playerInvulnerable();
  virtual void playerVulnerable();

  virtual void update();
  virtual void draw();
  virtual void clean();

  //Adding ammo to give to the player
  int Ammo;
  double ammoRespawn;
  bool invulnerable;

  enum vertices {
	F0, F1, F2, F3, 
  };
 
  private:
  double score;

};

#endif // PLAYER_H_
