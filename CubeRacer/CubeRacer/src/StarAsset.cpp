#include "StarAsset.h"

StarAsset::StarAsset() 
  : GameAsset(
	      string("shaders/hello-gl.v.glsl")
	      , string("shaders/starAsset.f.glsl")
	      )
{
  StarAsset(0, 0, 0);
}

StarAsset::StarAsset(float x, float y, float z) 
  : GameAsset(
      string("shaders/hello-gl.v.glsl"), 
      string("shaders/starAsset-gl.f.glsl")
){

  // A default "unit" Star
  num_vertices = 12;
  num_triangles = 20;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]{

  //     x      y     z     //www.clipartbest.com/cliparts/dir/aAp/diraAp9i9.jpeg
	-0.65,	-1.0,	 0.0,	//Bottom left point		F0
	 0.65,	-1.0,	 0.0,	//Bottom right point		F1
	 0.0,	-0.5,	 0.0,	//Bottom middle point		F2
	
	-0.4,	-0.2,	 0.0,	//Lower-middle left point	F3
	 0.4,	-0.2,	 0.0,	//Lower-middle right point	F4

	-1.0,	 0.25,	 0.0,	//Middle left-most point	F5
	 1.0,	 0.25,	 0.0,	//Middle right-most point	F6
	-0.25,	 0.3,	 0.0,	//Middle left point		F7
	 0.25,	 0.3,	 0.0,	//Middle right point		F8

	 0.0,	 1.0,	 0.0,	//Top point			F9
	 0.0,	 0.0,	 0.5,	//Middle Front point		F10
	 0.0,	 0.0,	-0.5	//Middle Back point		F11	
	
}; // three points per vertex

  g_element_buffer_data = new GLushort[num_triangles * 3]{

	F10, F3,  F0,	//Bottom left point
	F0,  F2,  F10,

	F10, F2,  F1,	//Bottom right point
	F1,  F4,  F10,

	F10, F4,  F6,	//Middle right point
	F6,  F8,  F10,
	
	F10, F8,  F9,	//Top point
	F9,  F7,  F10,

	F10, F7,  F5,	//Middle left point
	F5,  F3,  F10,

	F11, F3,  F0,
	F0,  F2,  F11,
	
	F11, F2, F1,
	F1,  F4, F11,

	F11, F4, F6,
	F6,  F8, F11,

	F11, F8, F9,
	F9,  F7, F11,

	F11, F7, F5,
	F7,  F3, F11	

}; // three vertices per triangle

  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));

  make_resources();
}

StarAsset::~StarAsset() {
  // TODO: do something nice and fun here.
}

void StarAsset::update() {
  if (isAlive) {
    shared_ptr<Point3> p = shared_ptr<Point3>(new Point3(this->bbox->getCentre()->getX(), -0.3, this->bbox->getCentre()->getZ()-0.2));

    bbox.reset();
    bbox = shared_ptr<BoundingBox>(new BoundingBox(*p, 1.0, 1.0, 1.0));
    if( this->bbox->getCentre()->getZ() < -5) { this->dead(); }
  }
}

bool StarAsset::collidesWith(Player & a) {
  return bbox->collidesWith((*a.bbox));
}

void StarAsset::draw() {
  GameAsset::draw();
}

void StarAsset::clean() { } 
