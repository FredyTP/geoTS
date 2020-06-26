// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorCollection.h"
#include "CollectionSubscriptor.generated.h"


UCLASS( ClassGroup=(Custom),Blueprintable, meta=(BlueprintSpawnableComponent) )
class GEOTS_API UCollectionSubscriptor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollectionSubscriptor();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite)
		FString CollectionTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CollectionTagInit;

	UFUNCTION(BlueprintCallable)
		void Subscript(FString tag);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bSubscripted;

	UPROPERTY(BlueprintReadOnly)
		AActorCollection* _collection;
		

};
