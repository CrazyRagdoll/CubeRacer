#define GLEW_STATIC // Easier debugging
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <list>
#include <time.h>
#include <unistd.h>

#include "GameAsset.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "StarAsset.h"
#include "HeartAsset.h"
#include "Camera.h"

using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00;

//Is the game running?
bool running = true;

//Adding the player to the game
shared_ptr<Player> player ;

//Adding the assets and enemy assets into the game
vector<shared_ptr<GameAsset>> assets;
vector<shared_ptr<Enemy>> enemies;
vector<shared_ptr<Enemy>> tmpEnemies;
vector<shared_ptr<Bullet>> bullets;
vector<shared_ptr<Bullet>> tmpBullets;

//PLAYING WITH STARS!!! WOOOO
vector<shared_ptr<StarAsset>> stars;
vector<shared_ptr<StarAsset>> tmpStars;
int StarCount = 0;
int StarSpawnRate = rand() % 500 + rand () % 200 + 100;

//ADDING A HEART POWER_UP!!!!!!
vector<shared_ptr<HeartAsset>> hearts;
vector<shared_ptr<HeartAsset>> tmpHearts;
int HeartCount = 0;
int HeartSpawnRate = rand() % 1000 + rand () % 500 + 200;
int invulnerableDuration = 0;
int invulnerableEnd = 250;

//Global variable to hold the "difficulty" of the game
double Diffy = 0.15;

//Crude Enemy counter to help regulate enemy spawn rates.
int EnemyCount = 0;
int EnemySpawnRate = 40;
int EnemiesPerSpawn = 8;

//Clock used in my implementation to help time the game - currently used to increase difficulty as the game plays out
clock_t t;

SDL_Window * window = nullptr;

/*
 * SDL timers run in separate threads.  In the timer thread
 * push an event onto the event queue.  This event signifies
 * to call display() from the thread in which the OpenGL 
 * context was created.
 */
Uint32 display(Uint32 interval, void *param) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = RUN_GRAPHICS_DISPLAY;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
	return interval;
}

void display() {

  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  //Increase EnemyCount, HeartCount & StarCount by 1
  EnemyCount++;
  StarCount++;
  HeartCount++;

  //Calculating the time to deal with difficulty 
  t = clock();
  double time = ((float)t/CLOCKS_PER_SEC) * 1.5;
	
  //Giving the player an extra bullet every 5 seconds
  if((fmod(time, player->getAmmoRate()) < 0.002) && (fmod(time, player->getAmmoRate()) > 0)){ 
    player->changeAmmo(1); 
  }

  //Spawning some stars!
  if(player->isAlive){
    if(fmod(StarCount, StarSpawnRate) == 0 ){
      int rnd = rand() % 20 - 10;
      stars.push_back(shared_ptr<StarAsset> (new StarAsset(player->bbox->getCentre()->getX() + rnd, -0.3, 50)));
    }
  }    

  //Spawning some hearts!
  if(player->isAlive){
    if(fmod(HeartCount, HeartSpawnRate) == 0 ){
      int rnd = rand() % 30 - 15;
      hearts.push_back(shared_ptr<HeartAsset> (new HeartAsset(player->bbox->getCentre()->getX() + rnd, 0.0, 50)));
    }
  }

  //If the player is alive spawn enemies every time the count increments by 20.
  if(player->isAlive){
    if(fmod(EnemyCount, EnemySpawnRate) == 0 ){
      //get the position of the player to spawn the enemies infront of him but 25 		  blocks back.
      int pos  = int(player->bbox->getCentre()->getX());
      for( int n_2 = 0; n_2 <= EnemiesPerSpawn; n_2++ ){
	int rnd = rand() % 60 - 30;
	enemies.push_back(shared_ptr<Enemy> (new Enemy(pos + rnd, 0, 25)));
      }
    }
  }

  //Collision detection between the player and enemies.
  if(!player->invulnerable) {
    for(auto i : enemies) { 
      if( i->collidesWith(*player)){
	player->dead();
      }else { /*i->dead();*/ } //if the players invulnerable kill the enemy asset
    }
  }

  //
  if(player->invulnerable) {
    for(auto i : enemies) {
      if( i->collidesWith(*player)){
	i->dead();
      }
    }
  }

  //Collision detection between the stars and player
  for(auto i : stars) {
    if( i->collidesWith(*player)){
      i->dead();
      player->incScore(50);
    }
  }

  //Collision detection between the hearts and player
  for(auto i : hearts) {
    if( i->collidesWith(*player)){
      i->dead();
      player->playerInvulnerable();
    }
  }

  //Collision detection between the enemies and bullets
  for(auto j : bullets) {
    for(auto i : enemies) {
      if( j->collidesWith(*i)){
	i->dead();
	j->dead();
      }
    }
  } 

  if(player->invulnerable)
  {
     invulnerableDuration++;
  } else { invulnerableDuration = 0; }

  if(fmod(invulnerableDuration, invulnerableEnd) == 0)
  {
    player->playerVulnerable();
  }
  
  //Setting different difficulty values over time to make the game harder the longer you 	play.
  for(auto it : enemies){
    it->setDiff(Diffy);
    }
  if((fmod(time, 0.5) < 0.002) && (fmod(time, 0.5) > 0.0)){ 
      Diffy += 0.01; 
    } 

  //clearing the temp list of enemies, bullets and stars
  tmpEnemies.clear();
  tmpBullets.clear();
  tmpStars.clear();
  tmpHearts.clear();
  
  //Updating the assets
  for(auto it : enemies) { it->update(); }
  for(auto it : bullets) { it->update(); }
  for(auto it : stars)   { it->update(); }
  for(auto it : hearts)  { it->update(); }
  player->update();

  //adding the enemies, bullets & stars to the temp list 
  for(auto it : enemies) { if(it->isAlive) { tmpEnemies.push_back(it); }}
  for(auto it : bullets) { if(it->isAlive) { tmpBullets.push_back(it); }}
  for(auto it : stars)   { if(it->isAlive) { tmpStars.push_back(it);   }}
  for(auto it : hearts)  { if(it->isAlive) { tmpHearts.push_back(it);  }}

  //Drawing the assets onto the game
  for(auto it : enemies) { it->draw(); }
  for(auto it : bullets) { it->draw(); }
  for(auto it : stars)   { it->draw(); }
  for(auto it : hearts)  { it->draw(); }
  player->draw();

  //swapping the enemies, bullets & stars lists with the alive enemies, bullets & stars
  enemies.swap(tmpEnemies);
  bullets.swap(tmpBullets);
  stars.swap(tmpStars);
  hearts.swap(tmpHearts);

  if(!player->isAlive){ running = false; SDL_Quit(); }

  // Don't forget to swap the buffers
  SDL_GL_SwapWindow(window);
}

int main(int argc, char ** argv) {
	SDL_Surface * surf;
	Uint32 width = 640;
	Uint32 height = 480;
	Uint32 colour_depth = 16; // in bits
	Uint32 delay = 1000/60; // in milliseconds

	// Initialise SDL - when using C/C++ it's common to have to
	// initialise libraries by calling a function within them.
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
			cout << "Failed to initialise SDL: " << SDL_GetError() << endl;
			SDL_Quit();
	}

	// When we close a window quit the SDL application
	atexit(SDL_Quit);

	// Create a new window with an OpenGL surface
	window = SDL_CreateWindow("CI224 - Game ~~ CubeRunner LITE!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (nullptr == window) {
		cout << "Failed to create SDL window: " << SDL_GetError() << endl;
		SDL_Quit();
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (nullptr == glContext) {
		cout << "Failed to create OpenGL context: " << SDL_GetError() << endl;
		SDL_Quit();
	}

	// Initialise GLEW - an easy way to ensure OpenGl 2.0+
	// The *must* be done after we have set the video mode - otherwise we have no OpenGL context.
	glewInit();
	if (!glewIsSupported("GL_VERSION_2_0")) {
	  cerr<< "OpenGL 2.0 not available" << endl;
	  return 1;
	}	

	//Adding the players coordinates into the game
	player = shared_ptr<Player> (new Player(0, 0, 0));

  //Test adding a heart
  hearts.push_back(shared_ptr<HeartAsset> (new HeartAsset(0, 0, 10)));

	// Set the camera to be looking down at the player and give them a good field of view
	Camera::getInstance().setCamera(Camera::getInstance().getCameraM() * Matrix4::translation(Vector3(0.0, -2.0, 5.0)));
	display();

	// Add the main event loop
	SDL_Event event;

	while (running) {
	  while (SDL_PollEvent(&event)) {
	    switch (event.type) {

	      case SDL_QUIT:
		running = false;
		SDL_Quit();
		break;

	      case SDL_USEREVENT:
		display();
		break;

	      case SDL_KEYDOWN:
		Matrix4 camera = Camera::getInstance().getCameraM();
	      
	      switch(event.key.keysym.sym){
		case SDLK_UP:
		  //Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, 0.0, -5.0)));
		  break; 

		case SDLK_DOWN:
		  //Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.0, 0.0, 5.0))); 
		  break;

		case SDLK_ESCAPE:
		  SDL_Quit();
		  running = false;
		  break;
		
		case SDLK_LEFT:
		{
		  //Introducing similtanious player and camera movement.
		  Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(0.5, 0.0, 0.0)) ); 
		  player->move(-0.5);
	 	}		 
		break;
			  
		case SDLK_RIGHT:
		{ //Introducing similtanious player and camera movement.
		  Camera::getInstance().setCamera(camera * Matrix4::translation(Vector3(-0.5, 0.0, 0.0)) );
		  player->move(0.5);
		}	
		break;

		case SDLK_SPACE:
		{ //Adding player controlled bullets into the game.
		  if(player->Ammo >= 1)
		  {		
		    bullets.push_back(shared_ptr<Bullet> (new Bullet(double(player->bbox->getCentre()->getX()),0,0)));
		    player->changeAmmo(-1);
		  }
		}
		default:
	        break;
	      }
	      break;
	    }
	  }
	SDL_Delay(16);	
	display();
	}
} //NatsuSt
