#include "FloorAsset.h"

FloorAsset::FloorAsset() 
  : GameAsset(
	      string("shaders/hello-gl.v.glsl")
	      , string("shaders/hello-gl.f.glsl")
	      )
{
  FloorAsset(0, 0, 0);
}

FloorAsset::FloorAsset(float x, float y, float z) {
  this->li = nullptr;

  // A default "unit" Floor
  num_vertices = 8;
  num_triangles = 12;
  g_vertex_buffer_data = new GLfloat[num_vertices * 3]{

  //     x      y     z
	-0.5, -0.5,  0.5, //F - 0
	 0.5, -0.5,  0.5, //F - 1
	-0.5,  0.5,  0.5, //F - 2
	 0.5,  0.5,  0.5, //F - 3
	-0.5, -0.5, -0.5, //B - 4
	 0.5, -0.5, -0.5, //B - 5
	-0.5,  0.5, -0.5, //B - 6
	 0.5,  0.5, -0.5  //B - 7
}; // three points per vertex

  g_element_buffer_data = new GLushort[num_triangles * 3]{

	F0, F1, F2,  //front
	F1, F3, F2,

	F1, B5, F3,  //right
	B5, B7, F3,

	B5, B4, B7,  //back
	B4, B6, B7,

	B4, F0, B6,  //left
	F0, F2, B6,

	F2, F3, B6,  //top
	F3, B7, B6,

	B4, B5, F0,  //bottom
	B5, F1, F0
	
}; // three vertices per triangle

/* We do not need a bounding box for the floor as there will be no collisions with it as I will be using a "magicY" axis	
  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));
*/

  make_resources();
}

FloorAsset::~FloorAsset() {
  // TODO: do something nice and fun here.
}

void FloorAsset::update() {
  if (nullptr != li) {
    //    std::cout << "x: " << bbox->getCentre()->getX() << "\ty: " << bbox->getCentre()->getY() << "\tz:" << bbox->getCentre()->getZ() << std::endl;
    shared_ptr<Point3> p = shared_ptr<Point3>(new Point3(this->li->update()));

   // bbox.reset();
   // bbox = shared_ptr<BoundingBox>(new BoundingBox(*p, 1.0, 1.0, 1.0));
  }
}

void FloorAsset::setInterpolator(shared_ptr<IInterpolator> li) {
  this->li.swap(li);
}

void FloorAsset::draw() {
//  std::cout << "x: " << bbox->getCentre()->getX() << "\ty: " << bbox->getCentre()->getY() << "\tz:" << bbox->getCentre()->getZ() << std::endl;
  GameAsset::draw();
}
