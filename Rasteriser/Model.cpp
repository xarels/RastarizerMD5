#include "Model.h"


Model::Model()
{

}

Model::~Model()
{
}

Model::Model(const Model& rhs)
{
	 _polygons = rhs._polygons;
	 _normalPolygons = rhs._normalPolygons;
	 _vertices = rhs._vertices;
	 _transformVertices = rhs._transformVertices;

	 for (int i = 0; i < 3; i++)
	 {
		 ka_ambientReflectanceCoeficient[i] = rhs.ka_ambientReflectanceCoeficient[i];
		 kd_diffuseReflectanceCoeficient[i] = rhs.kd_diffuseReflectanceCoeficient[i];
	 }
}

std::vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

std::vector<Vertex>& Model::GetVertices()
{
	return _transformVertices;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

void Model::AddVertex(float x, float y, float z)
{
	_vertices.emplace_back(x, y, z);
	_transformVertices.emplace_back(x, y, z);
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.emplace_back(i0, i1, i2);
}

void Model::ApplyTransformToLocalVertices(const Matrix &transform)
{
	for (int i = 0; i < _vertices.size(); i++)
	{
		_transformVertices[i] = transform * _vertices[i];
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix &transform)
{
	for (int i = 0; i < _transformVertices.size(); i++)
	{
		_transformVertices[i] = transform * _transformVertices[i];
	}
}

void Model::DehomogenizeAll()
{
	for (int i = 0; i < _transformVertices.size(); i++)
	{
		_transformVertices[i].dehomogenizeVertices();
	}											
}

void Model::CalculateBackfaces(Vertex Cam_position)
{
	int polygonSize = (int) GetPolygonCount();

	for (int i = 0; i < polygonSize; i++)
	{	 
		_polygons[i].DecideCulling(_transformVertices, Cam_position);
	}
}

void Model::CalculateDirectionalLight(std::vector<DirectionalLight> dirLight)
{
	int polygonSize = (int)GetPolygonCount();

	for (int i = 0; i < polygonSize; i++)
	{
		_polygons[i].CheckDirectionalLight(dirLight, kd_diffuseReflectanceCoeficient);
	}
}

void Model::CalculateAmbientLight(AmbientLight ambientLight)
{
	int polygonSize = (int)GetPolygonCount();

	for (int i = 0; i < polygonSize; i++)
	{
		_polygons[i].CheckAmbientLight(ambientLight, ka_ambientReflectanceCoeficient);
	}
}

void Model::CalculatePointLight(std::vector<PointLight> pointLight)
{
	int polygonSize = (int)GetPolygonCount();

	for (int i = 0; i < polygonSize; i++)
	{
		_polygons[i].CheckPointLight(pointLight, kd_diffuseReflectanceCoeficient, _transformVertices);
	}
}

void Model::CalculateDirectionalLightShading(std::vector<DirectionalLight> dirLight)
{
	int polygonSize = (int)GetPolygonCount();

	for (int i = 0; i < polygonSize; i++)
	{
		_polygons[i].CheckDirectionalLightShading(dirLight, kd_diffuseReflectanceCoeficient);
	}
}

bool CompareSort(Polygon3D &a, Polygon3D &b)
{
	return a.GetAverageZDepth() > b.GetAverageZDepth();
}

void Model::Sort(void)
{
	float averageZDepth = 0;

	int polygonSize = (int)GetPolygonCount();
	for (int i = 0; i < polygonSize; i++)
	{
		averageZDepth = GetVertices()[GetPolygons()[i].GetIndex(0)].GetZ() +
						GetVertices()[GetPolygons()[i].GetIndex(1)].GetZ() +
						GetVertices()[GetPolygons()[i].GetIndex(2)].GetZ() / 3;

		_polygons[i].SetAverageZDepth(averageZDepth);
	}
	std::sort(_polygons.begin(), _polygons.end(), CompareSort);
}

void Model::CalculateNormalForVertices()
{
	int vertexSize = (int)GetVertexCount();
	int polygonSize = (int)GetPolygonCount();
	Vector3D v = Vector3D(0, 0, 0);
	Vector3D v2 = Vector3D(0, 0, 0);

	for (int i = 0; i < vertexSize; i++)
	{
		_transformVertices[i].SetNormal(Vector3D(0, 0, 0));
		_transformVertices[i].SetContributionCount(0);

		for (int j = 0; j < polygonSize; j++)
		{
			_transformVertices[_polygons[j].GetIndex(0)].SetNormal(_polygons[j].GetNormalVector());
			_transformVertices[_polygons[j].GetIndex(0)].CountContribution();

			_transformVertices[_polygons[j].GetIndex(1)].SetNormal(_polygons[j].GetNormalVector());
			_transformVertices[_polygons[j].GetIndex(1)].CountContribution();

			_transformVertices[_polygons[j].GetIndex(2)].SetNormal(_polygons[j].GetNormalVector());
			_transformVertices[_polygons[j].GetIndex(2)].CountContribution();
		}

		v = v + _transformVertices[i].GetNormal();
		v2 = v / _transformVertices[i].GetContributionCount();
		v2.NormaliseVector3D();
	}
}

void Model::CheckAmbientLightVertex(AmbientLight amb)
{
	const int minRGB = 0;
	const int maxRGB = 255;

	float tempRGB[3] = { 0.0f, 0.0f, 0.0f };

	// get light intensity stored in polygon class
	tempRGB[0] = amb.GetRColor();
	tempRGB[1] = amb.GetGColor();
	tempRGB[2] = amb.GetBColor();


	for (int j = 0; j < GetPolygonCount(); j++)
	{
		for (int i = 0; i < 3; i++)
		{
			//Multiplies temp by diffuse refflectance
			tempRGB[i] *= ka_ambientReflectanceCoeficient[i];

			// clamps R,G,B values || Ternary for If statement
			tempRGB[i] = tempRGB[i] < minRGB ? minRGB : tempRGB[i];
			tempRGB[i] = tempRGB[i] > maxRGB ? maxRGB : tempRGB[i];

			//Stores colours in polygon
			_transformVertices[_polygons[j].GetIndex(i)].SetGColor(tempRGB[0]);
			_transformVertices[_polygons[j].GetIndex(i)].SetGColor(tempRGB[1]);
			_transformVertices[_polygons[j].GetIndex(i)].SetGColor(tempRGB[2]);
		}
	}
}


void Model::CheckDirectionalLightVertex(std::vector<DirectionalLight> dirLight)
{
	Vector3D directionalLightSource;
	//temp variables
	float tempRGB[3] = { 0.0f, 0.0f, 0.0f };
	float total[3] = { 0.0f, 0.0f, 0.0f };
	const int minRGB = 0;
	const int maxRGB = 255;
	float dotProduct = 0.0f;
	Vector3D vNormal;

	int dirLightSize = (int)dirLight.size();
	int polygonSize = (int)GetPolygonCount();

	for (int i = 0; i < polygonSize; i++)
	{
		for (int j = 0; j < dirLightSize; j++)
		{
			for (int c = 0; c < 3; c++)
			{

				// gets light intensity
				tempRGB[0] = dirLight[j].GetRColor();
				tempRGB[1] = dirLight[j].GetGColor();
				tempRGB[2] = dirLight[j].GetBColor();

				//Gets light intensity stored in polygons
				total[0] = GetVertices()[GetPolygons()[i].GetIndex(c)].GetRColor();
				total[1] = GetVertices()[GetPolygons()[i].GetIndex(c)].GetGColor();
				total[2] = GetVertices()[GetPolygons()[i].GetIndex(c)].GetBColor();

				//Multiplies temp by light coeficiency
				tempRGB[c] *= kd_diffuseReflectanceCoeficient[c];

				// Gets normal vector
				vNormal = _transformVertices[GetPolygons()[i].GetIndex(c)].GetNormal();

				directionalLightSource = dirLight[j].GetDirection();
				directionalLightSource.NormaliseVector3D();

				//Calculates dot product between normal polygon and direction of light
				dotProduct = Vector3D::DotProduct(directionalLightSource, vNormal);

				if (dotProduct > 0.0f)
				{
					//Multiplies temporary variable by dot product
					tempRGB[c] *= dotProduct;

					//Add temporary variable to total
					total[c] += tempRGB[c];

					// clamps R,G,B values || Lambda expression for if statement
					total[c] = total[c] < minRGB ? minRGB : total[c];
					total[c] = total[c] > maxRGB ? maxRGB : total[c];

					//Stores colours in polygon
					GetVertices()[GetPolygons()[i].GetIndex(c)].SetRColor(total[0]);
					GetVertices()[GetPolygons()[i].GetIndex(c)].SetGColor(total[1]);
					GetVertices()[GetPolygons()[i].GetIndex(c)].SetBColor(total[2]);
				}
			}
		}
	}
}

void Model::CheckPointLightVertex(std::vector<PointLight> pointLight)
{
	//temp variables
	float tempRGB[3] = { 0.0f, 0.0f, 0.0f };
	float total[3] = { 0.0f, 0.0f, 0.0f };
	const int minRGB = 0;
	const int maxRGB = 255;
	float dotProduct = 0.0f;

	float attenuation = 0.0f;
	Vector3D normal;
	Vector3D lightSource;
	Vertex v;

	int pointLightSize = (int)pointLight.size();
	int pSize = (int)GetPolygonCount();

	for (int j = 0; j < pointLightSize; j++)
	{
		//get light intensity stored in polygon class  <-- error here
		total[0] = v.GetRColor();
		total[1] = v.GetGColor();
		total[2] = v.GetBColor();

		// gets light intensity stored in pointLight
		tempRGB[0] = pointLight[j].GetRColor();
		tempRGB[1] = pointLight[j].GetGColor();
		tempRGB[2] = pointLight[j].GetBColor();

		//Multiplies temp by diffuse refflectance
		tempRGB[0] *= kd_diffuseReflectanceCoeficient[0];
		tempRGB[1] *= kd_diffuseReflectanceCoeficient[1];
		tempRGB[2] *= kd_diffuseReflectanceCoeficient[2];

		// Gets normal vector
		normal = v.GetNormal();

		for (int i = 0; i < pSize; i++)
		{
			//get light source vector
			lightSource = pointLight[j].GetLightSource() - _transformVertices[_polygons[i].GetIndex(0)];

			//sets distance
			pointLight[j].SetAttenDistance((int)lightSource.GetLength());

			//normalises light source
			lightSource.NormaliseVector3D();

			//Calculates dot product between normal polygon and direction of light
			dotProduct = Vector3D::DotProduct(lightSource, normal);

			if (dotProduct > 0.0f)
			{
				//Calculates Attenuation
				attenuation = (float)1 / pointLight[j].GetAttenA() +
					(pointLight[j].GetAttenB() *
					pointLight[j].GetAttenDistance()) +
					pointLight[j].GetAttenC() *
					(float)pow(pointLight[j].GetAttenDistance(), 2);

				for (int k = 0; k < 3; i++)
				{
					//Multiplies temporary variable by dot product
					tempRGB[k] *= dotProduct;

					//multiplies temporary var by attenuation
					tempRGB[k] *= attenuation;

					//Add temporary variable to total
					total[k] += tempRGB[i];

					// clamps R,G,B values || ternary for if statement
					total[k] = total[k] < minRGB ? minRGB : total[k];
					total[k] = total[k] > maxRGB ? maxRGB : total[k];
				}
				//Stores colours in polygon
				v.SetRColor(total[0]);
				v.SetGColor(total[1]);
				v.SetBColor(total[2]);
			}
		}
	}
}