// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDataQueryComponent.h"
#include <Kismet\GameplayStatics.h>

// Sets default values for this component's properties
UBaseDataQueryComponent::UBaseDataQueryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseDataQueryComponent::BeginPlay()
{
	Super::BeginPlay();

	//Search the manager in the world and bind to data event
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr)
	{
		TArray<AActor*> found;
		TSubclassOf<ADataManager> toFind;
		UGameplayStatics::GetAllActorsOfClass(TheWorld, ADataManager::StaticClass(), found);
		if (found.Num() > 0)
		{
			_dataManager = Cast<ADataManager>(found[0]);
			if (_dataManager != nullptr)
			{
				//_manager->getMutex()->lock();
				_dataManager->OnDataUpdated.AddUObject(this, &UBaseDataQueryComponent::OnDataUpdated);
				//_manager->getMutex()->unlock();
			}
		}
	}
	// ...
	
}


// Called every frame
void UBaseDataQueryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseDataQueryComponent::OnDataUpdated_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Error, calling UBaseDataQueryComponent::OnDataUpdated_Implementation function, implement your own!!"));
}