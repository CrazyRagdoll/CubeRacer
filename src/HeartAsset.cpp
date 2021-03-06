#include "HeartAsset.h"

HeartAsset::HeartAsset() 
  : GameAsset(
	      string("CubeRacer/shaders/hello-gl.v.glsl")
	      , string("CubeRacer/shaders/heartAsset.f.glsl")
	      )
{
  HeartAsset(0, 0, 0);
}

HeartAsset::HeartAsset(float x, float y, float z) 
  : GameAsset(
      string("CubeRacer/shaders/hello-gl.v.glsl"), 
      string("CubeRacer/shaders/heartAsset-gl.f.glsl")
){

  // A default "unit" Heart
  num_vertices = 6;
  num_triangles = 4;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]{

  //     x      y     z     //http://www.google.co.uk/imgres?imgurl=&imgrefurl=http%3A%2F%2Fcollectionphotos.com%2Fnice-love-hearts%2F&h=0&w=0&tbnid=KXbXdSvz8eslGM&zoom=1&tbnh=180&tbnw=200&docid=USx2IhSCYzdRuM&tbm=isch&ei=cV1iU5SwK6fC0QXj3IDICg&ved=0CBEQsCUoBQ

	0.0,	0.4,	0.0,	//Middle Top		F0
	0.4,	0.8,	0.0,
	0.8,	0.4,	0.0,
	
	-0.4,	0.8,	0.0,
	-0.8,	0.4,	0.0,
	
	0.0,	-0.8,	0.0
	
	
}; // three points per vertex

  g_element_buffer_data = new GLushort[num_triangles * 3]{

	F0, F1, F2,	//Bottom left point
	F4, F3, F0,
	F2, F5, F0,
	F0, F5, F4


}; // three vertices per triangle

  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));

  make_resources();
}

HeartAsset::~HeartAsset() {
  // TODO: do something nice and fun here.
}

void HeartAsset::update() {
  if (isAlive) {
    shared_ptr<Point3> p = shared_ptr<Point3>(new Point3(this->bbox->getCentre()->getX(), -0.3, this->bbox->getCentre()->getZ()-0.3));

    bbox.reset();
    bbox = shared_ptr<BoundingBox>(new BoundingBox(*p, 1.0, 1.0, 1.0));
    if( this->bbox->getCentre()->getZ() < -5) { this->dead(); }
  } 
}

bool HeartAsset::collidesWith(Player & a) {
  return bbox->collidesWith((*a.bbox));
}

void HeartAsset::draw() {
  GameAsset::draw();
}

void HeartAsset::clean() { } 
