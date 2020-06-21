// Fill out your copyright notice in the Description page of Project Settings.


#include "DataRotationComponent.h"

// Sets default values for this component's properties
UDataRotationComponent::UDataRotationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDataRotationComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UDataRotationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDataRotationComponent::OnDataUpdated()
{
	float tsValue = _dataManager->getEnum(variable).value;
	FRotator result = (Rotation1 - Rotation0)* ((tsValue - value0) / (value1 - value0)) + Rotation0;
	this->GetAttachParent()->SetRelativeRotation(result);
}
