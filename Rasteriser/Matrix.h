#pragma once
#include "Vertex.h"
#include "Math.h"
#include <initializer_list>

#define M_PI 3.14159265358979323846264338327950288

class Matrix
{
public:
	//Matrix dimensions
	const int rows = 4;
	const int columns = 4;

	//Constructors
	Matrix();
	Matrix(std::initializer_list<float> list);

	//Copy Constructor
	Matrix(const Matrix& other);

	//Destructor
	~Matrix();

	//Accessors
	float GetM(const int row, const int column) const;
	void SetM(const int row, const int column, const float value);

	//Operators
	Matrix& operator= (const Matrix &rhs);
	const Matrix operator*(const Matrix &other) const;
	const Vertex operator*(const Vertex &other) const;

	//Identity Matrix
	static Matrix IdentityMatrix();

	//Transformations
	static Matrix Translation(float x, float y, float z);
	static Matrix Scaling(float x, float y, float z);
	static Matrix XRotation(float angle);
	static Matrix YRotation(float angle);
	static Matrix ZRotation(float angle);
	static Matrix XYZRotation(float angleX, float angleY, float angleZ);

	//Radians might be needed later...
	static float Radians(float angle);

private:
	float _m[4][4];
	void Copy(const Matrix& other);
};
