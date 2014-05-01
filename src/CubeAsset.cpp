#include "CubeAsset.h"

CubeAsset::CubeAsset() 
  : GameAsset(
	      string("CubeRacer/shaders/hello-gl.v.glsl")
	      , string("CubeRacer/shaders/hello-gl.f.glsl")
	      )
{
  CubeAsset(0, 0, 0);
}

CubeAsset::CubeAsset(float x, float y, float z) {

  // A default "unit" cube
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

  bbox.reset();
  bbox = shared_ptr<BoundingBox>(new BoundingBox(Point3(x, y, z), 1.0, 1.0, 1.0));

  make_resources();
}

CubeAsset::~CubeAsset() {
  // TODO: do something nice and fun here.
}

void CubeAsset::update() {
}

void CubeAsset::draw() {
//  std::cout << "x: " << bbox->getCentre()->getX() << "\ty: " << bbox->getCentre()->getY() << "\tz:" << bbox->getCentre()->getZ() << std::endl;
  GameAsset::draw();
}

void CubeAsset::clean() { } 
