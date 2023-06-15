#pragma once
#include "Vector3D.h"
#include <vector>
#include "AmbientLight.h"
#include "PointLight.h"
#include "DirectionalLight.h"

class Polygon3D
{
public:
	//Constructors
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);

	//Destructor
	~Polygon3D();

	//Copy Constructor
	Polygon3D(const Polygon3D& v);

	//Accessors
	int GetIndex(int) const;

	bool GetToBeCulled() const;
	void SetToBeCulled(const float doProduct);

	Vector3D GetNormalVector() const;
	void SetNormalVector(const Vector3D normal);

	float GetAverageZDepth() const;
	void SetAverageZDepth(const float zDepth);

	float GetRColor() const;
	void SetRColor(const float r);
	float GetGColor() const;
	void SetGColor(const float g);
	float GetBColor() const;
	void SetBColor(const float b);

	//Operatprs
	Polygon3D& operator= (const Polygon3D &rhs);

	//Calculations
	void DecideCulling(std::vector<Vertex> _transformVertices, Vertex Cam_position);
	void CheckAmbientLight(AmbientLight ambientLight, float ka_ambientReflectanceCoeficient[3]);
	void CheckDirectionalLight(std::vector<DirectionalLight> dirLight, float diffuseReflectanceCoeficient[3]);
	void CheckPointLight(std::vector<PointLight> pointLight, float diffuseReflectanceCoeficient[3], std::vector<Vertex> _transformVertices);
	void CheckDirectionalLightShading(std::vector<DirectionalLight> dirLight, float kd_diffuseReflectanceCoeficient[3]);
	void CheckPointLightShading(std::vector<PointLight> pointLight, float kd_diffuseReflectanceCoeficient[3], std::vector<Vertex> _transformVertices);

private:
	int _indices[3];
	bool _cullMarking = NULL;
	Vector3D _normal;
	float _averageZDepth;
	float _r;
	float _g;
	float _b;
};