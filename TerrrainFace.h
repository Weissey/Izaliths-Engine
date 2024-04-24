#include "Maths.h"
#include "Mesh.h"

#pragma once


class TerrainFace
{
public:
	
	Mesh* mesh;
	int reso;
	Vec3<float> localUp;
	Vec3<float> axisA;
	Vec3<float> axisB;

	TerrainFace(Mesh mesh, int resolution, Vec3<float> localUp) {
		this->mesh = &mesh;
		this->localUp.set(localUp.x, localUp.y, localUp.z);
		this->reso = resolution;

		axisA.set(localUp.y, localUp.z, localUp.x);
		axisB = crossProduct(localUp, axisA);
	}


    void ConstructMesh()
    {
        
    }
private:

};