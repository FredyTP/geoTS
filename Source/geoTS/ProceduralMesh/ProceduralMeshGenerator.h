// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <functional>

#include "CoreMinimal.h"
#include "ProceduralMeshGenerator.generated.h"

#define CONST_PI 3.14159265359
#define CONST_PI_2 6.28318530718
/**
 * 
 */
UCLASS(Blueprintable)
class GEOTS_API UProceduralMeshGenerator : public UObject
{
	GENERATED_BODY()
public:
	UProceduralMeshGenerator();
	~UProceduralMeshGenerator();
	UFUNCTION(BlueprintCallable, Category = ProceduralMesh)
		static void GetRegularPoly(int _sides, int size, TArray<FVector>& outVertex, TArray<int>& outTriangle, TArray<FVector>& outNormal, TArray<FVector2D>& outTextCoord);
	UFUNCTION(BlueprintCallable, Category = ProceduralMesh)
		static void GetCilinder(int _sides, float h, float r, int axis, TArray<FVector>& outVertex, TArray<int>& outTriangle, TArray<FVector>& outNormal, TArray<FVector2D>& outTextCoord);

	static void GetSurface(TFunction<FVector(float, float)> surfParam ,FVector2D min, FVector2D max, FVector2D detail, bool doubleFace, TArray<FVector>& outVertex, TArray<int>& outTriangle, TArray<FVector>& outNormal, TArray<FVector2D>& outTextCoord);
	
	static FVector getNormalParam(TFunction<FVector(float, float)> f, float t, float k, float h = 0.00001f);
	
};
