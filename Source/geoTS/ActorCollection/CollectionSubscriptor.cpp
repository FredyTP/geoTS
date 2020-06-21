// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionSubscriptor.h"
#include <Kismet\GameplayStatics.h>

// Sets default values for this component's properties
UCollectionSubscriptor::UCollectionSubscriptor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCollectionSubscriptor::BeginPlay()
{
	Super::BeginPlay();
	CollectionTag = CollectionTagInit;
	//Search the ActorColection in the world to suscript
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr)
	{
		TArray<AActor*> found;
		
		UGameplayStatics::GetAllActorsOfClass(TheWorld, AActorCollection::StaticClass(), found);
		if (found.Num() > 0)
		{
			_collection = Cast<AActorCollection>(found[0]);
			if (_collection != nullptr)
			{
				_collection->SubscriptActor(this->GetOwner(), CollectionTag);
			}
		}
	}
	
}


// Called every frame
void UCollectionSubscriptor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

