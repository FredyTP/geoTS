// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorCollection.h"

// Sets default values
AActorCollection::AActorCollection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorCollection::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorCollection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorCollection::SubscriptActor(AActor* toSuscript, FString CollectionTag)
{
	if (!_actorCollection.Contains(CollectionTag))
	{
		_actorCollection.Add(CollectionTag);
		_tagCollection.Add(CollectionTag);
	}
	_actorCollection[CollectionTag].AddUnique(toSuscript);
}

void AActorCollection::UnSubscriptActor(AActor* toUnSubscript, FString CollectionTag)
{
	if (_actorCollection.Contains(CollectionTag))
	{
		_actorCollection[CollectionTag].Remove(toUnSubscript);

		if (_actorCollection[CollectionTag].Num() == 0)
		{
			_tagCollection.Remove(CollectionTag);
		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AActorCollection::UnSubscriptActor : %s tag NOT FOUND"), *CollectionTag);
	}
	
	
}
void AActorCollection::UnSubscriptActor_All(AActor* toUnSubscript)
{
	for (auto &list : _actorCollection)
	{
		list.Value.Remove(toUnSubscript);

		if (list.Value.Num()==0)
		{
			_tagCollection.Remove(list.Key);
		}
		
	}
}
void AActorCollection::setCollectionVisibility(bool v, FString CollectionTag)
{

	if (_actorCollection.Contains(CollectionTag))
	{
		for (auto& a : _actorCollection[CollectionTag])
		{
			a->SetActorHiddenInGame(!v);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AActorCollection::setCollectionVisibility : %s tag NOT FOUND"), *CollectionTag);
	}


}

void AActorCollection::setCollectionVisibility_All(bool v)
{
	for (auto& list : _actorCollection)
	{
		for (auto& a :list.Value)
		{
			a->SetActorHiddenInGame(!v);
		}
	}
}
