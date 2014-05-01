#include "Player.h"

Player::Player() 
  : GameAsset(
	      string("CubeRacer/shaders/hello-gl.v.glsl")
	      , string("CubeRacer/shaders/player-gl.f.glsl")
	      )
{
  Player(0, 0, 0);
}

Player::Player(float x, float y, float z): Ammo(3) , ammoRespawn(2.0) , score(0) , invulnerable(false) {

  // A default "unit" cube
  num_vertices = 4;
  num_triangles = 4;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]{

  //     x      y     z
	-0.5, -0.5, -0.5, //F - 0  //base of the triangle player
	 0.5, -0.5, -0.5, //F - 1
	 0.0, -0.5,  0.5, //F - 2
	 0.0,  0.0,  0.0, //F - 3  //top point og the triangle player
	
}; // three points per vertex

  g_element_buffer_data = new GLushort[num_triangles * 3]{

	F0, F1, F2,   //Base
	F0, F1, F3,   //Back
	F1, F2, F3,   //RightSide
	F2, F0, F0    //LeftSide
	
}; // three vertices per triangle

  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));

  make_resources();
}

Player::~Player() {
  // TODO: do something nice and fun here.
}

void Player::update() {
  if (isAlive) 
  {
    score += 0.1;
    //cout << score << endl;
  }
  else
  { 
    cout << "You have died." << endl;
    cout << "Your Score: " << score << endl;
    this->clean();
    SDL_Quit();
  }
}

double Player::getAmmo(){
  return Ammo;
}

double Player::getAmmoRate(){
  return ammoRespawn;
}

void Player::changeAmmo(int ammoVal){
  Ammo = Ammo + ammoVal;
}

void Player::playerInvulnerable(){
  invulnerable = true;
}

void Player::playerVulnerable(){
  invulnerable = false;
}

void Player::move(double moving){
  shared_ptr<Point3> move = this->bbox->getCentre();
  *move = Point3(move->getX() + moving, 0.0, 0.0);
  move.reset();
}

void Player::incScore(double points) {
  score = score + points;
}

void Player::draw() {
  GameAsset::draw();
}

void Player::clean() { }
