// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorCollection.generated.h"

UCLASS()
class GEOTS_API AActorCollection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorCollection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SubscriptActor(AActor* toSuscript, FString CollectionTag);
	UFUNCTION(BlueprintCallable)
		void UnSubscriptActor(AActor* toUnSubscript, FString CollectionTag);

	UFUNCTION(BlueprintCallable)
		void UnSubscriptActor_All(AActor* toUnSubscript);

	UFUNCTION(BlueprintCallable)
		void setCollectionVisibility(bool v,FString CollectionTag);

	UFUNCTION(BlueprintCallable)
		void setCollectionVisibility_All(bool v);

	UPROPERTY(VisibleAnywhere)
		TArray<FString> _tagCollection;

	TMap<FString,TArray<AActor*>> _actorCollection;

	//JUST TO UPDATE THE OBJECT
	UPROPERTY(EditAnywhere)
		bool bUpdate;
};
