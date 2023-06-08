#include "Matrix.h"

Matrix::Matrix()
{
	_m[rows][columns];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			_m[i][j] = 0.0f;
		}
	}
}

Matrix::Matrix(std::initializer_list<float> list)
{
	if (list.size() != rows * columns)
	{
		throw "Insufficient values supplied";
	}

	_m[rows][columns];
	auto iterator = list.begin();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			_m[i][j] = *iterator++;
		}
	}
}

Matrix::Matrix(const Matrix& other)
{
	_m [rows][columns];
	Copy(other);
}

Matrix::~Matrix()
{
}

float Matrix::GetM(const int row, const int column) const
{
	return _m[row][column];
}

void Matrix::SetM(const int row, const int column, const float value)
{
	_m[row][column] = value;
}

Matrix& Matrix::operator= (const Matrix &rhs)
{
	if (this != &rhs)
	{
		// Only do if not assigning to ourselves (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

const Matrix Matrix::operator*(const Matrix &other) const
{
	Matrix result;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			float resultValue = 0;

			for (int k = 0; k < rows; k++)
			{
				resultValue += _m[i][k] * other.GetM(k, j);
			}
			result.SetM(i, j, resultValue);
		}
	}
	return result;
}

const Vertex Matrix::operator*(const Vertex &other) const
{
	Vertex result = other;

	result.SetX(_m[0][0] * other.GetX() + _m[0][1] * other.GetY() + _m[0][2] * other.GetZ() + _m[0][3] * other.GetW());
	result.SetY(_m[1][0] * other.GetX() + _m[1][1] * other.GetY() + _m[1][2] * other.GetZ() + _m[1][3] * other.GetW());
	result.SetZ(_m[2][0] * other.GetX() + _m[2][1] * other.GetY() + _m[2][2] * other.GetZ() + _m[2][3] * other.GetW());
	result.SetW(_m[3][0] * other.GetX() + _m[3][1] * other.GetY() + _m[3][2] * other.GetZ() + _m[3][3] * other.GetW());

	return result;
}

// Private method to copy contents of one matrix
// to another
void Matrix::Copy(const Matrix & other)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			_m[i][j] = other.GetM(i, j);
		}
	}
}

Matrix Matrix::IdentityMatrix()
{
	return { 1.0,0.0,0.0,0.0,
			0.0,1.0,0.0,0.0,
			0.0,0.0,1.0,0.0,
			0.0,0.0,0.0,1.0 };
}

Matrix Matrix::Translation(float xTrans, float yTrans, float zTrans)
{
	return { 1.0, 0.0, 0.0, xTrans,
		     0.0, 1.0, 0.0, yTrans,
		     0.0, 0.0, 1.0, zTrans,
		     0.0, 0.0, 0.0, 1.0 };
}

Matrix Matrix::Scaling(float xScale, float yScale, float zScale)
{     
	return { xScale, 0.0, 0.0, 0.0,
	         0.0, yScale, 0.0, 0.0,
		     0.0, 0.0, zScale, 0.0,
		     0.0, 0.0, 0.0, 1.0};
}

Matrix Matrix::XRotation(float angle)
{
	return  { 1.0, 0.0, 0.0, 0.0,
		      0.0, (float)cos(angle), (float)-sin(angle), 0.0,
		      0.0, (float)sin(angle), (float)cos(angle), 0.0,
		      0.0, 0.0, 0.0, 1.0 };
}

Matrix Matrix::YRotation(float angle)
{
	return { (float)cos(angle), 0.0, (float)sin(angle), 0.0,
		      0.0, 1.0, 0.0, 0.0,
		      (float)-sin(angle), 0.0, (float)cos(angle), 0.0,
		      0.0, 0.0, 0.0, 1.0, };
}

Matrix Matrix::ZRotation(float angle)
{
	return { (float)cos(angle), (float)-sin(angle), 0.0, 0.0,
		     (float)sin(angle), (float)cos(angle), 0.0, 0.0,
		     0.0, 0.0, 1.0, 0.0,
		     0.0, 0.0, 0.0, 1.0 };
}

Matrix Matrix::XYZRotation(float angleX, float angleY, float angleZ)
{
	return ZRotation(angleZ)  * YRotation(angleY) * XRotation(angleX);
}

float Matrix::Radians(float angle)
{
	return (float) (angle * M_PI / 180.0);
}