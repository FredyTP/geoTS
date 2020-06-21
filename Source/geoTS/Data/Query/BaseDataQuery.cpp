// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDataQuery.h"
#include <Kismet\GameplayStatics.h>

// Sets default values
ABaseDataQuery::ABaseDataQuery()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseDataQuery::BeginPlay()
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
				_dataManager->OnDataUpdated.AddUObject(this, &ABaseDataQuery::OnDataUpdated);
				//_manager->getMutex()->unlock();
			}
		}
	}
}

// Called every frame
void ABaseDataQuery::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABaseDataQuery::OnDataUpdated_Implementation()
{

}

