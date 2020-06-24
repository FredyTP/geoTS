// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionSubscriptor.h"
#include <Kismet\GameplayStatics.h>

// Sets default values for this component's properties
UCollectionSubscriptor::UCollectionSubscriptor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	_collection = nullptr;
	bSubscripted = false;
	CollectionTag = CollectionTagInit;
	
	// ...
}


UCollectionSubscriptor::~UCollectionSubscriptor()
{

}

// Called when the game starts
void UCollectionSubscriptor::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UCollectionSubscriptor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCollectionSubscriptor::Subscript(FString tag)
{
	//Searches the ActorCollection in the world

		if (_collection == nullptr)
		{
			UWorld* TheWorld = GetWorld();
			if (TheWorld != nullptr)
			{
				TArray<AActor*> found;

				UGameplayStatics::GetAllActorsOfClass(TheWorld, AActorCollection::StaticClass(), found);
				if (found.Num() > 0)
				{
					_collection = Cast<AActorCollection>(found[0]);

				}
			}
		}
		//Subscripts the owner actor to the collection
		if (_collection != nullptr)
		{
			if (bSubscripted)
			{
				UE_LOG(LogTemp, Warning, TEXT("UCollectionSubscriptor::Subscript, error Actor: %s is already Subscripted"), *GetOwner()->GetName());
				_collection->UnSubscriptActor_All(this->GetOwner());
			}

			_collection->SubscriptActor(this->GetOwner(), tag);
			bSubscripted = true;
		}



}

