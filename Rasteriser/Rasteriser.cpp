#include "Rasteriser.h"

Rasteriser app; 
int ticks;

bool Rasteriser::Initialise()
{
	if (!MD2Loader::LoadModel("cube.md2", model, &Model::AddPolygon, &Model::AddVertex))
	{
		return false;
	}
	// Camera
	//camera = Camera(0, 0, 0, Vertex(0.0f, 0.0f, -40.0f, 1.0f));
	//camera = Camera(0, 0, 0, Vertex(0.0f, 0.0f, -50.0f, 1.0f));
	camera = Camera(0, 0, 0, Vertex(0.0f, 0.0f, -150.0f, 1.0f));

	//ambient Light
	ambLight = AmbientLight(28, 80, 120);
	//ambLight = AmbientLight(0, 0, 0);
	
	//Directional 
	//dirLight.emplace_back(DirectionalLight(0, 100, 0, Vector3D(1.0f, 0.0f, 1.0f)));   // default value 1,0,1 <-- change if needed
	dirLight.emplace_back(DirectionalLight(255, 221, 108, Vector3D(-2.0f, 1.0f, 2.0f)));   // default value 1,0,1 <-- change if needed


	//Point Light
	//pointLight.emplace_back(PointLight(28, 80, 120, Vertex(0.0f, -20.0f, -5.50f, 1.0f), 2.00f, 0.00f, 2.00f));
	pointLight.emplace_back(PointLight(10, 0, 0, Vertex(50.0f, -50.0f, 1.0f, -100.0f), 1.00f, 0.00f, 1.00f));

	ticks = 0;
	return true;
}

void Rasteriser::Update(Bitmap &bitmap)
{
	modelTransformation = Matrix::YRotation(0.05f) * modelTransformation;
	GeneratePerspectiveMatrix(1.0f, (float)bitmap.GetWidth() / bitmap.GetHeight());
	GenerateViewMatrix(1.0f, bitmap.GetWidth(), bitmap.GetHeight());
	ticks++;
}

void Rasteriser::Render(Bitmap &bitmap)
{
	// Clear the window to black
	bitmap.Clear(RGB(0, 0, 0));

	//Run Preview
	//CyclePreview(bitmap);
	//WireframeCycleNoCulling(bitmap);
	//WireframeCycleCullingSort(bitmap);
	//SmoothShadingCycle(bitmap);
    ThreeLightsCycle(bitmap);
	//BarycentricCycle(bitmap);
	//DirectionalCycle(bitmap);
}	

void Rasteriser::DrawWireFrameNoCulling(Bitmap &bitmap)
{
	HDC hdc = bitmap.GetDC();
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(28, 80, 120));
	int tempIndex[3] = { 0,0,0 };
	SelectObject(hdc, hPen);

	int polygonSize = (int) model.GetPolygonCount();
	for (int i = 0; i < polygonSize; i++)
	{
		tempIndex[0] = model.GetPolygons()[i].GetIndex(0);
		tempIndex[1] = model.GetPolygons()[i].GetIndex(1);
		tempIndex[2] = model.GetPolygons()[i].GetIndex(2);

		MoveToEx(hdc, (int) model.GetVertices()[tempIndex[0]].GetX(), (int) model.GetVertices()[tempIndex[0]].GetY(), NULL);
		LineTo(hdc, (int) model.GetVertices()[tempIndex[1]].GetX(), (int) model.GetVertices()[tempIndex[1]].GetY());
		LineTo(hdc, (int) model.GetVertices()[tempIndex[2]].GetX(), (int) model.GetVertices()[tempIndex[2]].GetY());
		LineTo(hdc, (int) model.GetVertices()[tempIndex[0]].GetX(), (int) model.GetVertices()[tempIndex[0]].GetY());
	}
	DeleteObject(hPen);
}

void Rasteriser::DrawWireFrame(Bitmap &bitmap)
{
	HDC hdc = bitmap.GetDC();
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(28, 80, 120));
	int tempIndex[3]{0,0,0};
	SelectObject(hdc, hPen);

	int polygonSize = (int)model.GetPolygonCount();
	for (int i = 0; i < polygonSize; i++)
	{
		if (model.GetPolygons()[i].GetToBeCulled() == false)
		{
			tempIndex[0] = model.GetPolygons()[i].GetIndex(0);
			tempIndex[1] = model.GetPolygons()[i].GetIndex(1);
			tempIndex[2] = model.GetPolygons()[i].GetIndex(2);

			MoveToEx(hdc, (int) model.GetVertices()[tempIndex[0]].GetX(), (int) model.GetVertices()[tempIndex[0]].GetY(), NULL);
			LineTo(hdc, (int) model.GetVertices()[tempIndex[1]].GetX(), (int) model.GetVertices()[tempIndex[1]].GetY());
			LineTo(hdc, (int) model.GetVertices()[tempIndex[2]].GetX(), (int) model.GetVertices()[tempIndex[2]].GetY());
			LineTo(hdc, (int) model.GetVertices()[tempIndex[0]].GetX(), (int) model.GetVertices()[tempIndex[0]].GetY());
		}
	}
	DeleteObject(hPen);
}

void Rasteriser::DrawSolidFlatColor(Bitmap &bitmap)
{
	POINT point[3]{0,0,0};													// array that holds 2d points
	HDC hdc = bitmap.GetDC();
	COLORREF color = RGB(28, 211, 162);
	/* Create brush and pen */
	HPEN hPen = CreatePen(PS_SOLID, 1, color);;
	HBRUSH hBrush = CreateSolidBrush(color);
	SelectObject(hdc, hPen);										
	SelectObject(hdc, hBrush);
	int tempIndex[3]{0,0,0};

	int polygonSize = (int)model.GetPolygonCount();
	for (int i = 0; i < polygonSize; i++)			// For each polygon draw point
	{
		if (model.GetPolygons()[i].GetToBeCulled() == false)
		{

			tempIndex[0] = model.GetPolygons()[i].GetIndex(0);
			tempIndex[1] = model.GetPolygons()[i].GetIndex(1);
			tempIndex[2] = model.GetPolygons()[i].GetIndex(2);

			point[0].x = (int)model.GetVertices()[tempIndex[0]].GetX();
			point[0].y = (int)model.GetVertices()[tempIndex[0]].GetY();
			point[1].x = (int)model.GetVertices()[tempIndex[1]].GetX();
			point[1].y = (int)model.GetVertices()[tempIndex[1]].GetY();
			point[2].x = (int)model.GetVertices()[tempIndex[2]].GetX();
			point[2].y = (int)model.GetVertices()[tempIndex[2]].GetY();

			Polygon(hdc, point, 3);
		}
	}
	DeleteObject(hPen);												// Delete pen
	DeleteObject(hBrush);
}

void Rasteriser::DrawSolidFlat(Bitmap &bitmap)
{
	POINT point[3]{0,0,0};													// array that holds 2d points
	HDC hdc = bitmap.GetDC();
	COLORREF color = RGB(28, 211, 162);
	/* Create brush and pen */
	HPEN hPen = nullptr;
	HBRUSH hBrush = nullptr;
	int tempIndex[3]{0,0,0};

	int polygonSize = (int)model.GetPolygonCount();
	for (int i = 0; i < polygonSize; i++)			// For each polygon draw point
	{
		if (model.GetPolygons()[i].GetToBeCulled() == false)
		{
			color = RGB(model.GetPolygons()[i].GetRColor(), model.GetPolygons()[i].GetGColor(), model.GetPolygons()[i].GetBColor());
			hPen = CreatePen(PS_SOLID, 1, color);
			hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);										// Select pen
			SelectObject(hdc, hBrush);

			tempIndex[0] = model.GetPolygons()[i].GetIndex(0);
			tempIndex[1] = model.GetPolygons()[i].GetIndex(1);
			tempIndex[2] = model.GetPolygons()[i].GetIndex(2);

			point[0].x = (int)model.GetVertices()[tempIndex[0]].GetX();
			point[0].y = (int)model.GetVertices()[tempIndex[0]].GetY();
			point[1].x = (int)model.GetVertices()[tempIndex[1]].GetX();
			point[1].y = (int)model.GetVertices()[tempIndex[1]].GetY();
			point[2].x = (int)model.GetVertices()[tempIndex[2]].GetX();
			point[2].y = (int)model.GetVertices()[tempIndex[2]].GetY();

			Polygon(hdc, point, 3);
			DeleteObject(hPen);												// Delete pen
			DeleteObject(hBrush);
		}
	}
}

void Rasteriser::MyDrawSolidFlat(Bitmap &bitmap)
{
	COLORREF Color = RGB(28, 211, 162);
	HDC hdc = bitmap.GetDC();
	int tempIndex[3]{ 0, 0, 0 };

	int polygonSize = (int)model.GetPolygonCount();
	for (int i = 0; i < polygonSize; i++)			// For each polygon draw point
	{
		if (model.GetPolygons()[i].GetToBeCulled() == false)
		{
			Color = RGB(model.GetPolygons()[i].GetRColor(), model.GetPolygons()[i].GetGColor(), model.GetPolygons()[i].GetBColor());

			tempIndex[0] = model.GetPolygons()[i].GetIndex(0);
			tempIndex[1] = model.GetPolygons()[i].GetIndex(1);
			tempIndex[2] = model.GetPolygons()[i].GetIndex(2);

			FillPolygonFlatBarycentric(bitmap,
										model.GetVertices()[tempIndex[0]],
										model.GetVertices()[tempIndex[1]],
										model.GetVertices()[tempIndex[2]],
										Color);
		}
	}
}

void Rasteriser::DrawSmoothShading(Bitmap &bitmap)
{
	HDC hdc = bitmap.GetDC();

	int tempIndex[3]{ 0, 0, 0 };

	int polygonSize = (int)model.GetPolygonCount();

	for (int i = 0; i < polygonSize; i++)			// For each polygon draw point
	{
		if (model.GetPolygons()[i].GetToBeCulled() == false)
		{
			tempIndex[0] = model.GetPolygons()[i].GetIndex(0);
			tempIndex[1] = model.GetPolygons()[i].GetIndex(1);
			tempIndex[2] = model.GetPolygons()[i].GetIndex(2);

			FillPolygonFlatBarycentricShading(bitmap,
				model.GetVertices()[tempIndex[0]],
				model.GetVertices()[tempIndex[1]],
				model.GetVertices()[tempIndex[2]]);
		}
	}
}

void Rasteriser::FillPolygonFlatBarycentricShading(Bitmap &bitmap, Vertex vt1, Vertex vt2, Vertex vt3)
{
	HDC hdc = bitmap.GetDC();

	Vector3D q = Vector3D(0, 0, 0);
	float s = 0.0f;
	float t = 0.0f;
	float sT = 0;

	/* color components differences betweeb v2 and v1 */
	int deltaRed12 = 0;
	int deltaGreen12 = 0;
	int deltaBlue12 = 0;

	/* color components differences betweeb v3 and v1 */
	int deltaRed13 = 0;
	int deltaGreen13 = 0;
	int deltaBlue13 = 0;

	int maxX = (int)max(vt1.GetX(), max(vt2.GetX(), vt3.GetX()));
	int minX = (int)min(vt1.GetX(), min(vt2.GetX(), vt3.GetX()));
	int maxY = (int)max(vt1.GetY(), max(vt2.GetY(), vt3.GetY()));
	int minY = (int)min(vt1.GetY(), min(vt2.GetY(), vt3.GetY()));

	/* spanning vectors of edge (v1,v2) and (v1,v3) */
	Vector3D edge1 = vt2 - vt1;
	Vector3D edge2 = vt3 - vt1;

	deltaRed12 = (int)(vt2.GetRColor() - vt1.GetRColor());
	deltaGreen12 = (int)(vt2.GetGColor() - vt1.GetGColor());
	deltaBlue12 = (int)(vt2.GetBColor() - vt1.GetBColor());

	deltaRed13 = (int)(vt3.GetRColor() - vt1.GetRColor());
	deltaGreen13 = (int)(vt3.GetGColor() - vt1.GetGColor());
	deltaBlue13 = (int)(vt3.GetBColor() - vt1.GetBColor());

	int resRed = 0;
	int resGreen = 0;
	int resBlue = 0;

	/* iterate over each pixel of bounding box and check if it's inside
	* the traingle using the barycentirc approach.
	*/
	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			q = Vector3D(x - vt1.GetX(), y - vt1.GetY(), vt1.GetZ());

			s = Vector3D::CrossProductBarycentric(q, edge2) / Vector3D::CrossProductBarycentric(edge1, edge2);
			t = Vector3D::CrossProductBarycentric(edge1, q) / Vector3D::CrossProductBarycentric(edge1, edge2);

			sT = s + t;

			if ((s >= 0) && (t >= 0) && (sT <= 1))
			{
				resRed = (int)(vt1.GetRColor() + (s * deltaRed12) + (t * deltaRed13));
				resGreen = (int)(vt1.GetGColor() + (s * deltaGreen12) + (t * deltaGreen13));
				resBlue = (int)(vt1.GetBColor() + (s * deltaBlue12) + (t * deltaBlue13));

				SetPixel(hdc, x, y, RGB(resRed, resGreen, resBlue));
			}
		}
	}
}

void Rasteriser::FillPolygonFlatBarycentric(Bitmap &bitmap, Vertex vt1, Vertex vt2, Vertex vt3, COLORREF shading)
{
	HDC hdc = bitmap.GetDC();

	Vector3D q = Vector3D(0, 0, 0);
	float s = 0.0f;
	float t = 0.0f;
	float sT = 0;

	int maxX = (int)max(vt1.GetX(), max(vt2.GetX(), vt3.GetX()));
	int minX = (int)min(vt1.GetX(), min(vt2.GetX(), vt3.GetX()));
	int maxY = (int)max(vt1.GetY(), max(vt2.GetY(), vt3.GetY()));
	int minY = (int)min(vt1.GetY(), min(vt2.GetY(), vt3.GetY()));

	/* spanning vectors of edge (v1,v2) and (v1,v3) */
	Vector3D edge1 = vt2 - vt1;
	Vector3D edge2 = vt3 - vt1;

	/* iterate over each pixel of bounding box and check if it's inside
	* the traingle using the barycentirc approach.
	*/
	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			q = Vector3D(x - vt1.GetX(), y - vt1.GetY(), vt1.GetZ());
			s = Vector3D::CrossProductBarycentric(q, edge2) / Vector3D::CrossProductBarycentric(edge1, edge2);
			t = Vector3D::CrossProductBarycentric(edge1, q) / Vector3D::CrossProductBarycentric(edge1, edge2);
			sT = (s + t);

			if ((s >= 0) && (t >= 0) && (sT <= 1))
			{
				SetPixel(hdc, x, y, shading);
			}
		}
	}
}

void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	perspectiveTransformation = { d / aspectRatio, 0.0, 0.0, 0.0,
						  0.0, d, 0.0, 0.0,
						  0.0, 0.0, d, 0.0,
						  0.0, 0.0, 1.0, 0.0 };
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	screenTransformation = { (float)width / 2, 0, 0, (float)width / 2,
					 0, (float)-height / 2, 0, (float)height / 2,
					 0 , 0, d / 2, d / 2,
					 0, 0, 0, 1 };
}

void Rasteriser::DrawString(Bitmap &bitmap, LPCTSTR text)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));

		// Display the text string.  
		TextOut(hdc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}

void Rasteriser::WireframeCycleNoCulling(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	DrawWireFrameNoCulling(bitmap);
}

void Rasteriser::WireframeCycleCullingNoSort(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	//BackFaceCulling
	model.CalculateBackfaces(camera.GetPosition());
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	DrawWireFrame(bitmap);
}

void Rasteriser::WireframeCycleCullingSort(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	//BackFaceCulling
	model.CalculateBackfaces(camera.GetPosition());
	//sort
	model.Sort();
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	DrawWireFrame(bitmap);
}

void Rasteriser::DrawSolidCycle(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	// backface culling
	model.CalculateBackfaces(camera.GetPosition());
	// Sort
	model.Sort();
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	DrawSolidFlatColor(bitmap);
}

void Rasteriser::AmbientCycle(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	// backface culling
	model.CalculateBackfaces(camera.GetPosition());
	// Ambient Light
	model.CalculateAmbientLight(ambLight);
	//Sort
	model.Sort();
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	DrawSolidFlat(bitmap);
}

void Rasteriser::DirectionalCycle(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	// backface culling
	model.CalculateBackfaces(camera.GetPosition());
	// Ambient Light
	model.CalculateDirectionalLight(dirLight);
	//Sort
	model.Sort();
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	DrawSolidFlat(bitmap);
}

void Rasteriser::PointCycle(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	// backface culling
	model.CalculateBackfaces(camera.GetPosition());
	//PointLight
	model.CalculatePointLight(pointLight);
	//Sort
	model.Sort();
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	DrawSolidFlat(bitmap);
}

void Rasteriser::AmbientDirectionalCycle(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	// backface culling
	model.CalculateBackfaces(camera.GetPosition());
	//AmbientLight
	model.CalculateAmbientLight(ambLight);
	//DirectionalLight
	model.CalculateDirectionalLight(dirLight);
	//Sort
	model.Sort();
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	DrawSolidFlat(bitmap);
}

void Rasteriser::ThreeLightsCycle(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	// backface culling
	model.CalculateBackfaces(camera.GetPosition());
	//AmbientLight
	model.CalculateAmbientLight(ambLight);
	//directioncal light
	model.CalculateDirectionalLight(dirLight);
	//PointLight
	model.CalculatePointLight(pointLight);
	//Sort
	model.Sort();
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	DrawSolidFlat(bitmap);
}

void Rasteriser::BarycentricCycle(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	// backface culling
	model.CalculateBackfaces(camera.GetPosition());
	//AmbientLight
	model.CalculateAmbientLight(ambLight);
	//directioncal light
	model.CalculateDirectionalLight(dirLight);
	//PointLight
	model.CalculatePointLight(pointLight);
	//Sort
	model.Sort();
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	MyDrawSolidFlat(bitmap);
}

void Rasteriser::SmoothShadingCycle(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);

	//backface culling
	model.CalculateBackfaces(camera.GetPosition());

	// Normals for vertices
	model.CalculateNormalForVertices();

	//Ambient Light
	//model.CalculateAmbientLight(ambLight);
	model.CheckAmbientLightVertex(ambLight);

	//Directional Light
	//model.CalculateDirectionalLightShading(dirLight);
	model.CheckDirectionalLightVertex(dirLight);


	//Point Light
	//model.CalculatePointLight(pointLight);
	model.CheckPointLightVertex(pointLight);

	//Sort
	model.Sort();

	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);

	//DrawSolidFlat(bitmap);
	//MyDrawSolidFlat(bitmap);

	DrawSmoothShading(bitmap);
}

void Rasteriser::SmoothShadingDirectionalCycle(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	//backface culling
	model.CalculateBackfaces(camera.GetPosition());
	// Normals for vertices
	model.CalculateNormalForVertices();
	//Directional Light
	model.CheckDirectionalLightVertex(dirLight);
	//Sort
	model.Sort();
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	DrawSmoothShading(bitmap);
}

void Rasteriser::SmoothShadingPointCycle(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	//backface culling
	model.CalculateBackfaces(camera.GetPosition());
	// Normals for vertices
	model.CalculateNormalForVertices();
	//Point Light
	model.CheckPointLightVertex(pointLight);
	//Sort
	model.Sort();
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	DrawSmoothShading(bitmap);
}

void Rasteriser::SmoothShadingMixedLightsCycle(Bitmap& bitmap)
{
	// World Transformation
	model.ApplyTransformToLocalVertices(modelTransformation);
	//backface culling
	model.CalculateBackfaces(camera.GetPosition());
	// Normals for vertices
	model.CalculateNormalForVertices();
	//Ambient Light
	model.CheckAmbientLightVertex(ambLight);
	//Directional Light
	model.CheckDirectionalLightVertex(dirLight);
	//Point Light
	model.CheckPointLightVertex(pointLight);
	//Sort
	model.Sort();
	// Camera transformation
	model.ApplyTransformToTransformedVertices(camera.GetView());
	model.ApplyTransformToTransformedVertices(perspectiveTransformation);
	// Dehomogenize the transformed vertices
	model.DehomogenizeAll();
	// Apply the screen transformation to the transformed vertices in the model
	model.ApplyTransformToTransformedVertices(screenTransformation);
	DrawSmoothShading(bitmap);
}

void Rasteriser::CyclePreview(Bitmap& bitmap)
{
	if (ticks < 150)
	{
		DrawString(bitmap, L"WireFrame|No Culling");
		WireframeCycleNoCulling(bitmap);
	}
	else if (ticks > 150 && ticks < 300)
	{
		DrawString(bitmap, L"WireFrame|Culling|No Sort");
		WireframeCycleCullingNoSort(bitmap);
	}
	else if (ticks > 300 && ticks < 450)
	{
		DrawString(bitmap, L"WireFrame|Culling|Sort");
		WireframeCycleCullingSort(bitmap);
	}
	else if (ticks > 450 && ticks < 600)
	{
		DrawString(bitmap, L"Solid Shading");
		DrawSolidCycle(bitmap);
	}
	else if (ticks > 600 && ticks < 750)
	{
		DrawString(bitmap, L"Ambient Light");
		AmbientCycle(bitmap);
	}
	else if (ticks > 750 && ticks < 900)
	{
		DrawString(bitmap, L"Directional Light");
		DirectionalCycle(bitmap);
	}
	else if (ticks > 900 && ticks < 1050)
	{
		DrawString(bitmap, L"Point Light");
		PointCycle(bitmap);
	}
	else if (ticks > 1050 && ticks < 1200)
	{
		DrawString(bitmap, L"Ambient Light & Dir Light");
		AmbientDirectionalCycle(bitmap);
	}
	else if (ticks > 1200 && ticks < 1350)
	{
		DrawString(bitmap, L"Three Lights");
		ThreeLightsCycle(bitmap);
	}
	else if (ticks > 1350 && ticks < 1500)
	{
		DrawString(bitmap, L"Barycentric Solid Shading");
		BarycentricCycle(bitmap);
	}

	else if (ticks > 1500 && ticks < 1650)
	{
		DrawString(bitmap, L"SmoothShading");
		SmoothShadingCycle(bitmap);
	}
	else if (ticks > 1650 && ticks < 1800)
	{
		DrawString(bitmap, L"SmoothShading Directional Light");
		SmoothShadingDirectionalCycle(bitmap);
	}
	else if (ticks > 1800 && ticks < 1950)
	{
		DrawString(bitmap, L"SmoothShading Point Light");
		SmoothShadingPointCycle(bitmap);
	}
	else if (ticks > 1950 && ticks < 2100)
	{
		DrawString(bitmap, L"SmoothShading Mixed Lights");
		SmoothShadingMixedLightsCycle(bitmap);
	}
	else if (ticks == 2100)
	{
		ticks = 0;
	}
}