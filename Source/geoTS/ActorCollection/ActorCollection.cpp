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
	}
	_actorCollection[CollectionTag].AddUnique(toSuscript);
}

void AActorCollection::UnSubscriptActor(AActor* toUnSuscript, FString CollectionTag)
{
	if (_actorCollection.Contains(CollectionTag))
	{
		_actorCollection[CollectionTag].Remove(toUnSuscript);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AActorCollection::UnSubscriptActor : %s tag NOT FOUND"), *CollectionTag);
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
