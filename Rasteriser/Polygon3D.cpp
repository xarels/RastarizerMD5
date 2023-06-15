#include "Polygon3D.h"

//temp variables
float tempRGB[3] = { 0.0f, 0.0f, 0.0f };
float total[3] = { 0.0f, 0.0f, 0.0f };
const int minRGB = 0;
const int maxRGB = 255;
float dotProduct = 0.0f;

Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
	_cullMarking = NULL;
	_averageZDepth = 0;
	_r = 0.0f;
	_g = 0.0f;
	_b = 0.0f;
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_r = 0.0f;
	_g = 0.0f;
	_b = 0.0f;
}

Polygon3D::~Polygon3D()
{
}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	for (int i = 0; i < 3; i++)
	{
		_indices[i] = p.GetIndex(i);
	}
	_cullMarking = p._cullMarking;
	_averageZDepth = p._averageZDepth;
	_r = p._r;
	_g = p._g;
	_b = p._b;
}

int Polygon3D::GetIndex(int i) const
{
	return _indices[i];
}

bool Polygon3D::GetToBeCulled() const
{
	return _cullMarking;
}

void Polygon3D::SetToBeCulled(float dotProduct)
{
	// Polygon cull set to true if dot product > 0, else false
	_cullMarking = (dotProduct > 0.0f);
}

Vector3D Polygon3D::GetNormalVector() const
{
	return _normal;
}

void Polygon3D::SetNormalVector(const Vector3D normal)
{
	_normal = normal;
}

float Polygon3D::GetAverageZDepth() const
{
	return _averageZDepth;
}

void Polygon3D::SetAverageZDepth(const float zDepth)
{
	_averageZDepth = zDepth;
}

float Polygon3D::GetRColor() const
{
	return _r;
}

void Polygon3D::SetRColor(const float r)
{
	_r = r;
}

float Polygon3D::GetGColor() const
{
	return _g;
}

void Polygon3D::SetGColor(const float g)
{
	_g = g;
}

float Polygon3D::GetBColor() const
{
	return _b;
}

void Polygon3D::SetBColor(const float b)
{
	_b = b;
}

Polygon3D& Polygon3D::operator= (const Polygon3D &rhs)
{
	_indices[0] = rhs.GetIndex(0);
	_indices[1] = rhs.GetIndex(1);
	_indices[2] = rhs.GetIndex(2);
	_cullMarking = rhs.GetToBeCulled();
	_averageZDepth = rhs.GetAverageZDepth();
	_r = rhs._r;
	_g = rhs._g;
	_b = rhs._b;

	return *this;
}

void Polygon3D::DecideCulling(std::vector<Vertex> _transformVertices,Vertex Cam_position)
{
	Vector3D eye;
	Vector3D vector3DA;
	Vector3D vector3DB;
	Vector3D normal;

	//Gets Vector3D 
	vector3DA = _transformVertices[GetIndex(0)] - _transformVertices[GetIndex(1)];
	vector3DB = _transformVertices[GetIndex(0)] - _transformVertices[GetIndex(2)];
	eye = Cam_position - _transformVertices[GetIndex(0)];

	//Calculates cross product of Vector3D B & A
	normal = Vector3D::CrossProduct(vector3DB, vector3DA);

	//Normalise Vector3D
	normal.NormaliseVector3D();
	eye.NormaliseVector3D();

	//sets normal in polygon
	SetNormalVector(normal);

	//Calculates dot product between normal & eye
	dotProduct = Vector3D::DotProduct(normal, eye);

	//Sets culling
	SetToBeCulled(dotProduct);
}

void Polygon3D::CheckAmbientLight(AmbientLight ambientLight, float ka_ambientReflectanceCoeficient[3])
{
	// get light intensity stored in ambient light
	tempRGB[0] = ambientLight.GetRColor();
	tempRGB[1] = ambientLight.GetGColor();
	tempRGB[2] = ambientLight.GetBColor();

	for (int i = 0; i < 3; i++)
	{
		//Multiplies temp by diffuse refflectance
		tempRGB[i] *= ka_ambientReflectanceCoeficient[i];

		// clamps R,G,B values || Ternary for If statement
		tempRGB[i] = tempRGB[i] < minRGB ? minRGB : tempRGB[i];
		tempRGB[i] = tempRGB[i] > maxRGB ? maxRGB : tempRGB[i];
	}

	//Stores colours in polygon
	_r = tempRGB[0];
	_g = tempRGB[1];
	_b = tempRGB[2];
}

void Polygon3D::CheckDirectionalLight(std::vector<DirectionalLight> dirLight, float kd_diffuseReflectanceCoeficient[3])
{
	Vector3D polygonNormal;
	Vector3D directionalLightSource;
	total[0] = 0;
	total[1] = 0;
	total[2] = 0;

	int dirLightSize = (int)dirLight.size();
	for (int j = 0; j < dirLightSize; j++)
	{
		// gets light intensity
		tempRGB[0] = dirLight[j].GetRColor();
		tempRGB[1] = dirLight[j].GetGColor();
		tempRGB[2] = dirLight[j].GetBColor();

		//Multiplies temp by light coeficiency
		tempRGB[0] *= kd_diffuseReflectanceCoeficient[0];
		tempRGB[1] *= kd_diffuseReflectanceCoeficient[1];
		tempRGB[2] *= kd_diffuseReflectanceCoeficient[2];

		//Gets light intensity stored in polygons
		total[0] = _r;
		total[1] = _g;
		total[2] = _b;

		// Gets normal vector
		polygonNormal = GetNormalVector();

		directionalLightSource = dirLight[j].GetDirection();
		directionalLightSource.NormaliseVector3D();

		//Calculates dot product between normal polygon and direction of light
		dotProduct = Vector3D::DotProduct(directionalLightSource, polygonNormal);

		if (dotProduct > 0.0f)
		{
			for (int i = 0; i < 3; i++)
			{
				//Multiplies temporary variable by dot product
				tempRGB[i] *= dotProduct;

				//Add temporary variable to total
				total[i] += tempRGB[i];

				// clamps R,G,B values || Lambda expression for if statement
				total[i] = total[i] < minRGB ? minRGB : total[i];
				total[i] = total[i] > maxRGB ? maxRGB : total[i];
			}
			//Stores colours in polygon
			_r = total[0];
			_g = total[1];
			_b = total[2];
		}
	}
}

void Polygon3D::CheckPointLight(std::vector<PointLight> pointLight, float kd_diffuseReflectanceCoeficient[3], std::vector<Vertex> _transformVertices)
{
	float attenuation = 0.0f;

	Vector3D polygonNormal;
	Vector3D lightSource;

	total[0] = 0;
	total[1] = 0;
	total[2] = 0;

	int pointLightSize = (int)pointLight.size();
	for (int j = 0; j < pointLightSize; j++)
	{
		// gets light intensity stored in pointLight
		tempRGB[0] = pointLight[j].GetRColor();
		tempRGB[1] = pointLight[j].GetGColor();
		tempRGB[2] = pointLight[j].GetBColor();

		//Multiplies temp by diffuse refflectance
		tempRGB[0] *= kd_diffuseReflectanceCoeficient[0];
		tempRGB[1] *= kd_diffuseReflectanceCoeficient[1];
		tempRGB[2] *= kd_diffuseReflectanceCoeficient[2];

		//get light intensity stored in polygon class  <-- error here
		total[0] = _r;
		total[1] = _g;
		total[2] = _b;

		// Gets normal vector
		polygonNormal = GetNormalVector();

		//get light source vector
		lightSource = pointLight[j].GetLightSource() - _transformVertices[GetIndex(0)];

		//sets distance
		pointLight[j].SetAttenDistance((int)lightSource.GetLength());

		//normalises light source
		lightSource.NormaliseVector3D();

		//Calculates dot product between normal polygon and direction of light
		dotProduct = Vector3D::DotProduct(lightSource, polygonNormal);

		if (dotProduct > 0)
		{
			//Calculates Attenuation
			attenuation = (float)1 / pointLight[j].GetAttenA() +
				(pointLight[j].GetAttenB() *
					pointLight[j].GetAttenDistance()) +
				pointLight[j].GetAttenC() *
				(float)pow(pointLight[j].GetAttenDistance(), 2);

			for (int i = 0; i < 3; i++)
			{
				//Multiplies temporary variable by dot product
				tempRGB[i] *= dotProduct;

				//multiplies temporary var by attenuation
				tempRGB[i] *= attenuation;

				//Add temporary variable to total
				total[i] += tempRGB[i];

				// clamps R,G,B values || ternary for if statement
				total[i] = total[i] < minRGB ? minRGB : total[i];
				total[i] = total[i] > maxRGB ? maxRGB : total[i];
			}
			//Stores colours in polygon
			_r = total[0];
			_g = total[1];
			_b = total[2];
		}
	}
}
/*
void Polygon3D::CheckDirectionalLightShading(std::vector<DirectionalLight> dirLight, float kd_diffuseReflectanceCoeficient[3])
{
	Vector3D polygonNormal;
	Vector3D directionalLightSource;
	total[0] = 0;
	total[1] = 0;
	total[2] = 0;

	int dirLightSize = (int)dirLight.size();
	for (int j = 0; j < dirLightSize; j++)
	{
		// gets light intensity
		tempRGB[0] = dirLight[j].GetRColor();
		tempRGB[1] = dirLight[j].GetGColor();
		tempRGB[2] = dirLight[j].GetBColor();

		//Multiplies temp by light coeficiency
		tempRGB[0] *= kd_diffuseReflectanceCoeficient[0];
		tempRGB[1] *= kd_diffuseReflectanceCoeficient[1];
		tempRGB[2] *= kd_diffuseReflectanceCoeficient[2];

		//Gets light intensity stored in polygons
		total[0] = _r;
		total[1] = _g;
		total[2] = _b;

		// Gets normal vector
		polygonNormal = GetNormalVector();

		directionalLightSource = dirLight[j].GetDirection();
		directionalLightSource.NormaliseVector3D();

		//Calculates dot product between normal polygon and direction of light
		dotProduct = Vector3D::DotProduct(directionalLightSource, polygonNormal);

		if (dotProduct > 0.0f)
		{
			for (int i = 0; i < 3; i++)
			{
				//Multiplies temporary variable by dot product
				tempRGB[i] *= dotProduct;

				//Add temporary variable to total
				total[i] += tempRGB[i];

				// clamps R,G,B values || Lambda expression for if statement
				total[i] = total[i] < minRGB ? minRGB : total[i];
				total[i] = total[i] > maxRGB ? maxRGB : total[i];
			}
			//Stores colours in polygon
			_r = total[0];
			_g = total[1];
			_b = total[2];
		}
	}
}*/
