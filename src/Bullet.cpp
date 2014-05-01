#include "Bullet.h"

Bullet::Bullet() 
  : GameAsset(
	      string("CubeRacer/shaders/hello-gl.v.glsl")
	      , string("CubeRacer/shaders/hello-gl.f.glsl")
	      )
{
  Bullet(0, 0, 0);
}

Bullet::Bullet(float x, float y, float z) {

  // A default "unit" triangular pyramid
  num_vertices = 5;
  num_triangles = 6;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]; // three points per vertex
  g_element_buffer_data = new GLushort[num_triangles * 3]; // three vertices per triangle

  g_vertex_buffer_data[0]  = -0.125; //Bottom Left Point 0
  g_vertex_buffer_data[1]  = -0.125;
  g_vertex_buffer_data[2]  = -0.25;

  g_vertex_buffer_data[3]  =  0.125;  //Bottom Right Point 1
  g_vertex_buffer_data[4]  = -0.125;
  g_vertex_buffer_data[5]  = -0.25;

  g_vertex_buffer_data[6]  = -0.125;  //Top Left Point 2
  g_vertex_buffer_data[7]  =  0.125;
  g_vertex_buffer_data[8]  = -0.25;

  g_vertex_buffer_data[9]  =  0.125;  //Top Right Point 3
  g_vertex_buffer_data[10] =  0.125;
  g_vertex_buffer_data[11] = -0.25;
 
  g_vertex_buffer_data[12] =  0.0;  //Front point 4
  g_vertex_buffer_data[13] =  0.0;
  g_vertex_buffer_data[14] =  0.5;

  g_element_buffer_data[0]  = 0;
  g_element_buffer_data[1]  = 1;
  g_element_buffer_data[2]  = 2;

  g_element_buffer_data[3]  = 1;
  g_element_buffer_data[4]  = 3;
  g_element_buffer_data[5]  = 2;

  g_element_buffer_data[6]  = 2;
  g_element_buffer_data[7]  = 3;
  g_element_buffer_data[8]  = 4;

  g_element_buffer_data[9]  = 3;
  g_element_buffer_data[10] = 1;
  g_element_buffer_data[11] = 4;

  g_element_buffer_data[12] = 1;
  g_element_buffer_data[13] = 0;
  g_element_buffer_data[14] = 4;

  g_element_buffer_data[15] = 0;
  g_element_buffer_data[16] = 2;
  g_element_buffer_data[17] = 4;

  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 0.5, 0.5, 0.5));

  make_resources();
}

Bullet::~Bullet() {
  // TODO: do something nice here.
}

void Bullet::update() {

  if (isAlive) {
    shared_ptr<Point3> p = shared_ptr<Point3>(new Point3(this->bbox->getCentre()->getX(), 0, this->bbox->getCentre()->getZ() + 0.1));
    this->bbox.reset();
    this->bbox = shared_ptr<BoundingBox>(new BoundingBox(*p, 0.5, 0.5, 0.5));
    if( this->bbox->getCentre()->getZ() > 25) { this->dead(); }
  }
}

void Bullet::draw() {
//  std::cout << "x: " << bbox->getCentre()->getX() << "\ty: " << bbox->getCentre()->getY() << "\tz:" << bbox->getCentre()->getZ() << std::endl;
  GameAsset::draw();
}

void Bullet::clean() { }
