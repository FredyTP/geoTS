// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralMeshActor.h"

// Sets default values
AProceduralMeshActor::AProceduralMeshActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProceduralMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AProceduralMeshActor::ParametricSurfaceFunction_Implementation(float t, float k)
{
	float x, y, z;
	float k1 = 1.2f;
	float a = 1.5f;
	x = pow(k1, t) * (1 +  cos(k)) *  cos(t);
	y = pow(k1, t) * (1 +  cos(k)) *  sin(t);
	z = pow(k1, t) *  sin(k) - a * pow(k1, t);
	return FVector(x, y, z);
}

bool AProceduralMeshActor::CreateSurface(FVector2D min, FVector2D max, FVector2D detail, bool doubleFace, TArray<FVector>& outVertex, TArray<int>& outTriangle, TArray<FVector>& outNormal, TArray<FVector2D>& outTextCoord)
{
	TFunction<FVector(float, float)> function = [this](float t, float v)
	{
		return this->ParametricSurfaceFunction(t, v);
	};
	UProceduralMeshGenerator::GetSurface(function, min,max, detail, doubleFace, outVertex, outTriangle, outNormal, outTextCoord);
	return false;
}

// Called every frame
void AProceduralMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

