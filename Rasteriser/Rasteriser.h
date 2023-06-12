#pragma once
#include <vector>
#include "Framework.h"
#include "Matrix.h"
#include "MD2Loader.h"
#include "Model.h"
#include "Camera.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Update(Bitmap &bitmap);
	void Render(Bitmap &bitmap);

	void DrawString(Bitmap & bitmap, LPCTSTR text);

	//Cycles for presentation
	void WireframeCycleNoCulling(Bitmap & bitmap);
	void WireframeCycleCullingNoSort(Bitmap & bitmap);
	void WireframeCycleCullingSort(Bitmap & bitmap);
	void DrawSolidCycle(Bitmap & bitmap);
	void AmbientCycle(Bitmap & bitmap);
	void DirectionalCycle(Bitmap & bitmap);
	void PointCycle(Bitmap & bitmap);
	void AmbientDirectionalCycle(Bitmap & bitmap);
	void ThreeLightsCycle(Bitmap & bitmap);
	void BarycentricCycle(Bitmap & bitmap);
	void SmoothShadingCycle(Bitmap & bitmap);
	void SmoothShadingDirectionalCycle(Bitmap & bitmap);
	void SmoothShadingPointCycle(Bitmap & bitmap);
	void SmoothShadingMixedLightsCycle(Bitmap & bitmap);
	void CyclePreview(Bitmap & bitmap);

	//Drawing model
	void DrawWireFrame(Bitmap &bitmap);
	void DrawSolidFlatColor(Bitmap & bitmap);
	void DrawSolidFlat(Bitmap &bitmap);
	void DrawWireFrameNoCulling(Bitmap & bitmap);
	void MyDrawSolidFlat(Bitmap &bitmap);
	void DrawSmoothShading(Bitmap & bitmap);
	void FillPolygonFlatBarycentricShading(Bitmap & bitmap, Vertex vt1, Vertex vt2, Vertex vt3);
	void FillPolygonFlatBarycentric(Bitmap &bitmap, Vertex vt1, Vertex vt2, Vertex vt3, COLORREF shading);
	//void FillPolygonFlatGaroudShading(Bitmap& bitmap, Vertex vt1, Vertex vt2, Vertex vt3, Vertex vt4, Vertex vt5);

	//Generate matrices
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);

private:
	Model model;
	Matrix modelTransformation = Matrix::IdentityMatrix();
	Matrix perspectiveTransformation;
	Matrix screenTransformation;
	Camera camera;
	AmbientLight ambLight;
	std::vector<PointLight> pointLight;
	std::vector<DirectionalLight> dirLight;
};