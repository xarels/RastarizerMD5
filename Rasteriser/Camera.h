#pragma once
#include "Vertex.h"
#include "Matrix.h"

class Camera
{
public:
	//Constructors
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	//Destructor
	~Camera();
	//Copy Constructor
	Camera(const Camera & rhs);

	//Accessors
	Matrix GetView();
	Vertex GetPosition() const;
	Matrix GetCameraPosition() const;
	void SetCameraPosition(const Vertex position);

	//Camera Rotation
	void RotateX(float xRotation);
	void RotateY(float yRotation);
	void RotateZ(float zRotation);

	//Operators
	Camera& operator= (const Camera &camera);

private:
	Matrix _xRotation;
	Matrix _yRotation;
	Matrix _zRotation;
	Matrix _cameraView;
	Matrix _cameraPosition;
	Vertex _position;
};
