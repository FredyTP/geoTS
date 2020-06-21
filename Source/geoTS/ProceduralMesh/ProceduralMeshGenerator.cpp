// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralMeshGenerator.h"

UProceduralMeshGenerator::UProceduralMeshGenerator()
{
}

UProceduralMeshGenerator::~UProceduralMeshGenerator()
{
}
void UProceduralMeshGenerator::GetRegularPoly(int _sides, int size, TArray<FVector>& outVertex, TArray<int>& outTriangle, TArray<FVector>& outNormal, TArray<FVector2D>& outTextCoord)
{
	int sides = _sides;
	if (sides < 3) sides = 3;
	//add center//
	outVertex.Add(FVector(0.0f, 0.0f, 0.0f));
	outNormal.Add(FVector(0.0f, 0.0f, 1.0f));
	outTextCoord.Add(FVector2D(0.5f, 0.5f));

	float x;
	float y;
	for (int i = 1; i <= sides + 1; i++)
	{
		x = (float)(i) / sides * CONST_PI_2;
		y = sin(x);
		x = cos(x);
		outVertex.Add(size*FVector(x, y, 0.0f));
		outNormal.Add(FVector(0.0f, 0.0f, 1.0f));
		outTextCoord.Add(FVector2D(x / 2 + 0.5f, y / 2 + 0.5f));
		if (i > 1)
		{
			outTriangle.Add(0);
			outTriangle.Add(i);
			outTriangle.Add(i-1);
		}

	}
}
void UProceduralMeshGenerator::GetCilinder(int _sides, float h, float r, int axis, TArray<FVector>& outVertex, TArray<int>& outTriangle, TArray<FVector>& outNormal, TArray<FVector2D>& outTextCoord)
{
	//INVERTIR CARAS//
	int sides = _sides;
	if (sides < 3) sides = 3;
	if (r == 0) r = 0.0001;
	float x, y;

		for (int i = 0; i < sides + 1; i++)
		{
			x = (float)(i) / sides * CONST_PI_2;
			y = r * sin(x);
			x = r * cos(x);

			outVertex.Add(FVector(x, y, -h));
			outNormal.Add(FVector(x, y, 0));
			outTextCoord.Add(FVector2D((float)i / (sides), 0));

			outVertex.Add(FVector(x, y, h));
			outNormal.Add(FVector(x, y, 0));
			outTextCoord.Add(FVector2D((float)i / sides, 1));

			if (i > 0)
			{
				outTriangle.Add(2 * i);
				outTriangle.Add(2 * (i - 1));
				outTriangle.Add(2 * i - 1);

				outTriangle.Add(2 * i + 1);
				outTriangle.Add(2 * i);
				outTriangle.Add(2 * i - 1);

				//_plist->addTriangle(2 * i, 2 * (i - 1), 2 * i - 1);
				//_plist->addTriangle(2 * i + 1, 2 * i, 2 * i - 1);
			}
		}
		outTriangle.Add(0);
		outTriangle.Add((sides) * 2);
		outTriangle.Add((sides) * 2+1);

		outTriangle.Add(1);
		outTriangle.Add(0);
		outTriangle.Add((sides) * 2+1);
		
		//_plist->addTriangle(0, (sides) * 2, (sides) * 2 + 1);
		//_plist->addTriangle(1, 0, (sides) * 2 + 1);


		//add centers// 2l
		outVertex.Add(FVector(0.0f, 0, -h));
		outNormal.Add(FVector(0.0f, 0.0f, -1.0f));
		outTextCoord.Add(FVector2D(0.5f, 0.5f));

		int os = 2 * (sides + 1) + 1;
		for (int i = 0; i < sides; i++)
		{
			x = (float)(i) / sides * CONST_PI_2;
			y = r * sin(x);
			x = r * cos(x);
			outVertex.Add(FVector(x, y, -h));
			outNormal.Add(FVector(0.0f, 0.0f, -1.0f));
			outTextCoord.Add(FVector2D(x/r/ 2 + 0.5f, y/r / 2 + 0.5f));

			if (i > 0)
			{
				outTriangle.Add(os-1);
				outTriangle.Add(os+i-1);
				outTriangle.Add(os+i);
				//_plist->addTriangle(os - 1, os + i - 1, os + i);
			}
		}
		outTriangle.Add(os - 1);
		outTriangle.Add(os + sides - 1);
		outTriangle.Add(os);
		//_plist->addTriangle(os - 1, os + sides - 1, os);

		os = os + sides + 1;

		outVertex.Add(FVector(0.0f, 0.0f, h));
		outNormal.Add(FVector(0.0f, 0.0f, 1.0f));
		outTextCoord.Add(FVector2D(0.5f, 0.5f));
		for (int i = 0; i < sides; i++)
		{
			x = (float)(i) / sides * CONST_PI_2;
			y = r * sin(x);
			x = r * cos(x);
			outVertex.Add(FVector(x, y, h));
			outNormal.Add(FVector(0.0f, 0.0f, 1.0f));
			outTextCoord.Add(FVector2D(x/r / 2 + 0.5f, y/r / 2 + 0.5f));

			if (i > 0)
			{
				outTriangle.Add(os + i - 1);
				outTriangle.Add(os - 1);
				outTriangle.Add(os + i);
				//_plist->addTriangle(os + i - 1, os - 1, os + i);
			}
		}
		outTriangle.Add(os);
		outTriangle.Add(os + sides - 1);
		outTriangle.Add(os - 1);
		//_plist->addTriangle(os + sides - 1, os - 1, os);

}
void UProceduralMeshGenerator::GetSurface(TFunction<FVector(float, float)> surfParam,FVector2D min, FVector2D max, FVector2D detail, bool doubleFace, TArray<FVector>& outVertex, TArray<int>& outTriangle, TArray<FVector>& outNormal, TArray<FVector2D>& outTextCoord)
{
	float t, k;
	int tsteps, ksteps;
	FVector normal;
	FVector aux;
	/*if (npoints == bg::math::Vector2(-1, -1))
	{*/
	tsteps = detail.X * (float)(max.X - min.X);
	ksteps = detail.Y * (float)(max.Y - min.Y);
	//}
	/*else
	{
		xsteps = npoints.x();
		ysteps = npoints.y();
	}*/

	float dt = (max.X - min.X) / (tsteps - 1);
	float dk = (max.Y - min.Y) / (ksteps - 1);

	for (int i = 0; i < tsteps; i++)
	{
		for (int j = 0; j < ksteps; j++)
		{
			t = (float)i * dt + min.X;
			k = (float)j * dk + min.Y;
			outVertex.Add(surfParam(t, k));
			
			outTextCoord.Add(FVector2D((float)i / tsteps, (float)j / ksteps));
			FVector norm = getNormalParam(surfParam, t, k, 0.00001);
			outNormal.Add(norm*(-1));
			//aux = getNormalParam(surfParam, t, k, h);
			//normal.set(aux.x(), aux.z(), aux.y());
			//_plist->addNormal(normal.scale(-1));

			if (j > 0)
			{
				if (i > 0)
				{
					outTriangle.Add(i * ksteps + j);
					outTriangle.Add(i * ksteps + j - 1);
					outTriangle.Add((i - 1) * ksteps + j - 1);

					outTriangle.Add(i * ksteps + j);
					outTriangle.Add((i - 1) * ksteps + j - 1);
					outTriangle.Add((i - 1) * ksteps + j);

				}
			}

		}
	}
	if (doubleFace)
	{
		size_t offset = tsteps * ksteps;
		for (int i = 0; i < tsteps; i++)
		{
			for (int j = 0; j < ksteps; j++)
			{
				t = (float)i * dt + min.X;
				k = (float)j * dk + min.Y;

				outVertex.Add(surfParam(t, k));

				outTextCoord.Add(FVector2D((float)i / tsteps, (float)j / ksteps));
				FVector norm = getNormalParam(surfParam, t, k, 0.0001);
				outNormal.Add(norm);
				//aux = getNormalParam(surfParam, t, k, h);
				//normal.set(aux.x(), aux.y(), aux.z());
				//_plist->addNormal(normal);

				if (j > 0)
				{
					if (i > 0)
					{
						outTriangle.Add(i * ksteps + j);
						outTriangle.Add((i - 1) * ksteps + j - 1);
						outTriangle.Add(i * ksteps + j - 1);

						outTriangle.Add(i * ksteps + j);
						outTriangle.Add((i - 1) * ksteps + j);
						outTriangle.Add((i - 1) * ksteps + j - 1);



					}
				}

			}
		}
	}

}

FVector UProceduralMeshGenerator::getNormalParam(TFunction<FVector(float, float)> f, float t, float k, float h)
{
	FVector Origin(f(t, k));
	FVector v1(f(t + h, k));
	FVector v2(f(t, k + h));
	v1 = v1 - Origin;
	v2 = v2 - Origin;
	return FVector::CrossProduct(v1,v2);
}
