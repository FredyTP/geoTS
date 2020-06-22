// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDataQueryComponent.h"
#include "../Download/DataManager.h"

#include "DataRotationComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GEOTS_API UDataRotationComponent : public UBaseDataQueryComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UDataRotationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnDataUpdated();

	UPROPERTY(EditAnywhere)
		FRotator Rotation0;
	UPROPERTY(EditAnywhere)
		FRotator Rotation1;

	UPROPERTY(EditAnywhere)
		float value0;
	UPROPERTY(EditAnywhere)
		float value1;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<TestSiteVarEnum> variable;


};
