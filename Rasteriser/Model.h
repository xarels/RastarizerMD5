#pragma once
#include <vector>
#include <algorithm>
#include <math.h>
#include "Matrix.h"
#include "Vertex.h"
#include "Polygon3D.h"
#include "Vector3D.h"
#include "Camera.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include "DirectionalLight.h"

class Model
{
public:
	//Constructor
	Model();

	//Destructor
	~Model();

	Model(const Model& rhs);

	//Accessors
	std::vector<Polygon3D>& GetPolygons();
	std::vector<Vertex>& GetVertices();

	//Get size of list
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;

	// Add to the list
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);

	//Apply transformations
	void ApplyTransformToLocalVertices(const Matrix &transform);
	void ApplyTransformToTransformedVertices(const Matrix &transform);

	//Calculates vertex normal
	void CalculateNormalForVertices();

	//Calculates Light for each vertex
	void CheckAmbientLightVertex(AmbientLight amb);
	void CheckDirectionalLightVertex(std::vector<DirectionalLight> dirLight);
	void CheckPointLightVertex(std::vector<PointLight> pointLight);

	//Dehomogenize
	void DehomogenizeAll();

	//Backface Culling
	void CalculateBackfaces(Vertex Cam_position);

	//Calculate Directional Light
	void CalculateDirectionalLight(std::vector<DirectionalLight> dirLight);

	//Calculate Ambient Light
	void CalculateAmbientLight(AmbientLight ambientLight);	

	//Calculate Point Light
	void CalculatePointLight(std::vector<PointLight> pointLight);

	void CalculateDirectionalLightShading(std::vector<DirectionalLight> dirLight);

	//Sort
	void Sort(void);

private:
	std::vector<Polygon3D> _polygons;
	std::vector<Polygon3D> _normalPolygons;
	std::vector<Vertex> _vertices;
	std::vector<Vertex> _transformVertices;

	float ka_ambientReflectanceCoeficient[3] = {1.0f, 1.0f, 1.0f};
	float kd_diffuseReflectanceCoeficient[3] = {0.5f, 0.5f, 0.5f};
	//float ks_specularReflectanceCoeficient[3] = { 0.5f, 0.5f, 0.5f };
};
