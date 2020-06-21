// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Runtime/Online/HTTP/Public/HttpManager.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/HttpRetrySystem.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"

#include "TestSiteVar.h"
//STD
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <string>

#include "DataManager.generated.h"


UENUM(BlueprintType)
enum TestSiteVarEnum
{
	T_HP1 = 0, T_HP2, T_AMB1, T_GR1, T_3V1, T_3V2, T_3V3, T_3V4, FLOW1, PRES1,
	BHE1_1, BHE1_2, BHE1_3, BHE1_4, // BOREHOLE 1
	BHE2_1, BHE2_2, BHE2_3, BHE2_4, // BOREHOLE 2
	BHE3_1, BHE3_2, BHE3_3, BHE3_4, // BOREHOLE 3
	BHE4_1, BHE4_2, BHE4_3, BHE4_4, // BOREHOLE 4
	HEAT_PUMP, KF1, KF2, KF3, KF4, RES_TANK, // ON/OFF
};

//Evento para actualizar las variables
DECLARE_EVENT(ADataManager, FDataUpdated)

UCLASS()
class GEOTS_API ADataManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADataManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	//PARSE FUNCTIONS

	static int ParseDoc(ADataManager* manager);

	static float GetNumber(FString& file, FString& tag);
	static int FindTag(FString& file, FString& tag);
	static float FindNumber(FString& file, int ind);

	void generateVector();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void initDownload();
	static void ThreadFunction(ADataManager* manager);

	//Get functions
	FTestSiteVar get(const FString tag) const;
	FTestSiteVar get(int ind) const;

	UFUNCTION(BlueprintCallable)
	FTestSiteVar getEnum(TEnumAsByte<TestSiteVarEnum> var) const;

	int getIdx(const FString tag) const;

	FDataUpdated OnDataUpdated;

private:
	TArray<FTestSiteVar> geoVars; //UPDATED FTestSiteVarS

	std::thread _thread;
	mutable std::mutex _mutex;
	std::atomic<bool> _downloadReady;
	std::atomic<bool> _running;
	std::atomic<bool> _updated;
	FString doc;

};
