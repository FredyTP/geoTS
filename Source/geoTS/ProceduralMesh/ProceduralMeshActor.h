// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshGenerator.h"
#include "ProceduralMeshActor.generated.h"

UCLASS()
class GEOTS_API AProceduralMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralMeshActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UFUNCTION(BlueprintNativeEvent)
		FVector ParametricSurfaceFunction(float t, float k);
	UFUNCTION(BlueprintCallable)
		bool CreateSurface(FVector2D min, FVector2D max, FVector2D detail, bool doubleFace, TArray<FVector>& outVertex, TArray<int>& outTriangle, TArray<FVector>& outNormal, TArray<FVector2D>& outTextCoord);

	virtual void Tick(float DeltaTime) override;

};
