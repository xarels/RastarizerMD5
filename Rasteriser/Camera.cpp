#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_xRotation = Matrix::XRotation(xRotation);
	_yRotation = Matrix::YRotation(yRotation);
	_zRotation = Matrix::ZRotation(zRotation);
	_position = position;
	_cameraPosition = Matrix::Translation(-position.GetX(), -position.GetY(), -position.GetZ());
	_cameraView = _xRotation * _yRotation * _zRotation * _cameraPosition;
}

Camera::~Camera()
{
}

Camera::Camera(const Camera& rhs)
{
	_xRotation = rhs._xRotation;
	_yRotation = rhs._xRotation;
	_zRotation = rhs._zRotation;
	_position = rhs._position;
	_cameraPosition = rhs._cameraPosition;
	_cameraView = rhs._cameraView;
}

Matrix Camera::GetView() 
{
	_cameraView = _xRotation * _yRotation * _zRotation * _cameraPosition;
	return _cameraView;
}

Vertex Camera::GetPosition() const
{
	return _position;
}

Matrix Camera::GetCameraPosition() const
{
	return _cameraPosition;
}

void Camera::SetCameraPosition(const Vertex position)
{
	_cameraPosition = Matrix::Translation(-position.GetX(), -position.GetY(), -position.GetZ());
}

void Camera::RotateX(float xRotation)
{
	_xRotation = Matrix::XRotation(xRotation);
}

void Camera::RotateY(float yRotation)
{
	_yRotation = Matrix::YRotation(yRotation);
}

void Camera::RotateZ(float zRotation)
{
	_zRotation = Matrix::ZRotation(zRotation);
}

Camera& Camera::operator= (const Camera &rhs)
{
	if (this != &rhs)
	{
		_cameraPosition = rhs._cameraPosition;
		_cameraView = rhs._cameraView;
		_position = rhs._position;
		_xRotation = rhs._xRotation;
		_yRotation = rhs._yRotation;
		_zRotation = rhs._zRotation;
	}
	return *this;
}