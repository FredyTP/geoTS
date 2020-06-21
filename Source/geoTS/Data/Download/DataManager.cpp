// Fill out your copyright notice in the Description page of Project Settings.

#include "DataManager.h"

// Sets default values
ADataManager::ADataManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADataManager::BeginPlay()
{
	Super::BeginPlay();
	generateVector();

	_downloadReady = false;
	_running = true;
	_updated = false;
	initDownload();
	_thread = std::thread(ThreadFunction, this);
}
void ADataManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	_running = false;
	_thread.join();
	FHttpModule::Get().GetHttpManager().Flush(true);
}

// Called every frame
void ADataManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("TAMB: %f"), this->get("T_AMB1").value);
	if (_updated)
	{
		OnDataUpdated.Broadcast();
		_updated = false;
	}
}

void ADataManager::ThreadFunction(ADataManager* manager)
{
	//IMPROVE THE FUNC WITH OPTIONS TO CLOSE FASTER
	while (manager->_running)
	{
		if (manager->_downloadReady)
		{
			//LOCK MUTEX
			manager->_mutex.lock();

			ADataManager::ParseDoc(manager);

			//UNLOCK MUTEX
			manager->_mutex.unlock();
			manager->_updated = true;

			manager->_downloadReady = false;
			manager->initDownload();
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Leaving Thread"));
}
//Init data download
void ADataManager::initDownload()
{
	TSharedRef<IHttpRequest> http = FHttpModule::Get().CreateRequest();
	http->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr request, FHttpResponsePtr response, bool success) {
		doc = request->GetResponse()->GetContentAsString();
		_downloadReady = true;
		});
	http->SetURL(TEXT("http://158.42.102.222/awp//tabla.htm"));
	http->ProcessRequest();
}

int ADataManager::ParseDoc(ADataManager* manager)
{
	for (int i = 0; i < manager->geoVars.Num(); i++)
	{
		manager->geoVars[i].value = GetNumber(manager->doc, manager->geoVars[i].tag);
	}
	return 0;
}

float ADataManager::GetNumber(FString& file, FString& tag)
{
	int ind = FindTag(file, tag);
	if (ind >= 0)
		return FindNumber(file, ind);
	else
		return std::numeric_limits<float>::min();
}

int ADataManager::FindTag(FString& file, FString& tag)
{
	int file_it = 0;
	int count = 0;

	while (file_it < file.Len())
	{
		if (file[file_it] == tag[0])
		{
			for (int i = 0; i < tag.Len(); i++)
			{
				if (file[file_it + i] == tag[i])
				{
					count++;
				}
				else
				{
					count = 0;
					break;
				}
			}
			if (count == tag.Len())
			{
				return file_it + (int)tag.Len();
			}
		}
		file_it++;
	}
	return -1;
}

float ADataManager::FindNumber(FString& file, int ind)
{
	std::string num;
	num.resize(10);
	for (int i = ind; i < ind + 10; i++)
	{
		if (i > file.Len() - 10)
		{
			break;
		}
		if (file[i] >= '0' && file[i] <= '9' || file[i] == '.')
		{
			num[i - ind] = file[i];
		}
		else
		{
			break;
		}
	}
	return std::stof(num);
}

FTestSiteVar ADataManager::get(const FString tag) const
{
	std::lock_guard<std::mutex> lock(_mutex);
	FTestSiteVar result;
	for (int i = 0; i < geoVars.Num(); i++)
	{
		if (geoVars[i].name.Compare(tag) == 0)
		{
			result = geoVars[i];
		}
	}

	return result;
}

FTestSiteVar ADataManager::get(int ind) const
{
	std::lock_guard<std::mutex> lock(_mutex);
	FTestSiteVar result = geoVars[ind];
	return result;
}
FTestSiteVar ADataManager::getEnum(TEnumAsByte<TestSiteVarEnum> var) const
{
	std::lock_guard<std::mutex> lock(_mutex);
	FTestSiteVar result = geoVars[var];
	return result;
}
int ADataManager::getIdx(const FString tag) const
{
	for (int i = 0; i < geoVars.Num(); i++)
	{
		if (geoVars[i].name.Compare(tag) == 0)
		{
			return i;
		}
	}
	return 0;
}

void ADataManager::generateVector()
{
	FTestSiteVar T_HP1;
	FTestSiteVar T_HP2;
	FTestSiteVar T_AMB1;
	FTestSiteVar T_GR1;
	FTestSiteVar T_3V1;
	FTestSiteVar T_3V2;
	FTestSiteVar T_3V3;
	FTestSiteVar T_3V4;
	FTestSiteVar FLOW1;
	FTestSiteVar PRES1;
	//10

	//VARIABLE BHE1
	FTestSiteVar BHE1_1;
	FTestSiteVar BHE1_2;
	FTestSiteVar BHE1_3;
	FTestSiteVar BHE1_4;
	//14

	//VARIABLE BHE2
	FTestSiteVar BHE2_1;
	FTestSiteVar BHE2_2;
	FTestSiteVar BHE2_3;
	FTestSiteVar BHE2_4;
	//18

	//VARIABLE BHE3
	FTestSiteVar BHE3_1;
	FTestSiteVar BHE3_2;
	FTestSiteVar BHE3_3;
	FTestSiteVar BHE3_4;
	//22

	//VARIABLE BHE4
	FTestSiteVar BHE4_1;
	FTestSiteVar BHE4_2;
	FTestSiteVar BHE4_3;
	FTestSiteVar BHE4_4;
	//26

	//VARIABLES ON/OFF

	FTestSiteVar HEAT_PUMP;
	FTestSiteVar KF1;
	FTestSiteVar KF2;
	FTestSiteVar KF3;
	FTestSiteVar KF4;
	FTestSiteVar RES_TANK;

	T_HP1.name += "T_HP1";
	T_HP1.tag += "<td id=\"impulseBC\" class=\"dato\">";
	T_HP1.unit += "ºC";
	T_HP1.isBool = false;

	T_HP2.name += "T_HP2";
	T_HP2.tag += "<td id=\"returnBC\" class=\"dato\">";
	T_HP2.unit += "°C";
	T_HP2.isBool = false;

	T_AMB1.name += "T_AMB1";
	T_AMB1.tag += "<td id=\"ambientTp\" class=\"dato\">";
	T_AMB1.unit += "°C";
	T_AMB1.isBool = false;

	//
	T_GR1.name += "T_GR1";
	T_GR1.tag += "<td id=\"groundTp\" class=\"dato\">";
	T_GR1.unit += "°C";
	T_GR1.isBool = false;
	//
	T_3V1.name += "T_3V1";
	T_3V1.tag += "<td id=\"3wVOutput\"  class=\"dato\">";
	T_3V1.unit += "°C";
	T_3V1.isBool = false;
	//
	T_3V2.name += "T_3V2";
	T_3V2.tag += "<td id=\"3wVeInput\" class=\"dato\">";
	T_3V2.unit += "°C";
	T_3V2.isBool = false;

	//
	T_3V3.name += "T_3V3";
	T_3V3.tag += "<td id=\"3wVReturn\" class=\"dato\">";
	T_3V3.unit += "°C";
	T_3V3.isBool = false;
	//
	T_3V4.name += "T_3V4";
	T_3V4.tag += "<td id=\"tankTp\" class=\"dato\">";
	T_3V4.unit += "°C";
	T_3V4.isBool = false;

	FLOW1.name += "FLOW1";
	FLOW1.tag += "<td  id=\"flow1\"  class=\"dato\">";
	FLOW1.unit += "m^3/h";
	FLOW1.isBool = false;

	PRES1.name += "PRES1";
	PRES1.tag += "<td id=\"pressure1\" class=\"dato\">";
	PRES1.unit += "bar";
	PRES1.isBool = false;

	//VARIABLES BHE1

	BHE1_1.name += "BHE1_1";
	BHE1_1.tag += "<td id=\"bhe11\" class=\"dato\">";
	BHE1_1.unit += "°C";
	BHE1_1.isBool = false;

	BHE1_2.name += "BHE1_2";
	BHE1_2.tag += "<td id=\"bhe12\" class=\"dato\">";
	BHE1_2.unit += "°C";
	BHE1_2.isBool = false;

	BHE1_3.name += "BHE1_3";
	BHE1_3.tag += "<td id=\"bhe13\" class=\"dato\">";
	BHE1_3.unit += "°C";
	BHE1_3.isBool = false;

	BHE1_4.name += "BHE1_4";
	BHE1_4.tag += "<td id=\"bhe14\" class=\"dato\">";
	BHE1_4.unit += "°C";
	BHE1_4.isBool = false;

	//VARIABLES BHE2
	BHE2_1.name += "BHE2_1";
	BHE2_1.tag += "<td id=\"bhe21\" class=\"dato\">";
	BHE2_1.unit += "°C";
	BHE2_1.isBool = false;

	BHE2_2.name += "BHE2_2";
	BHE2_2.tag += "<td id=\"bhe22\" class=\"dato\">";
	BHE2_2.unit += "°C";
	BHE2_2.isBool = false;

	BHE2_3.name += "BHE2_3";
	BHE2_3.tag += "<td id=\"bhe23\" class=\"dato\">";
	BHE2_3.unit += "°C";
	BHE2_3.isBool = false;

	BHE2_4.name += "BHE2_4";
	BHE2_4.tag += "<td id=\"bhe24\" class=\"dato\">";
	BHE2_4.unit += "°C";
	BHE2_4.isBool = false;

	//VARIABLES BHE3
	BHE3_1.name += "BHE3_1";
	BHE3_1.tag += "<td id=\"bhe31\" class=\"dato\">";
	BHE3_1.unit += "°C";
	BHE3_1.isBool = false;

	BHE3_2.name += "BHE3_2";
	BHE3_2.tag += "<td id=\"bhe32\" class=\"dato\">";
	BHE3_2.unit += "°C";
	BHE3_2.isBool = false;

	BHE3_3.name += "BHE3_3";
	BHE3_3.tag += "<td id=\"bhe33\" class=\"dato\">";
	BHE3_3.unit += "°C";
	BHE3_3.isBool = false;

	BHE3_4.name += "BHE3_4";
	BHE3_4.tag += "<td id=\"bhe34\" class=\"dato\">";
	BHE3_4.unit += "°C";
	BHE3_4.isBool = false;

	////VARIABLES BHE4

	BHE4_1.name += "BHE4_1";
	BHE4_1.tag += "<td id=\"bhe41\" class=\"dato\">";
	BHE4_1.unit += "°C";
	BHE4_1.isBool = false;

	BHE4_2.name += "BHE4_2";
	BHE4_2.tag += "<td id=\"bhe42\" class=\"dato\">";
	BHE4_2.unit += "°C";
	BHE4_2.isBool = false;

	BHE4_3.name += "BHE4_3";
	BHE4_3.tag += "<td id=\"bhe43\" class=\"dato\">";
	BHE4_3.unit += "°C";
	BHE4_3.isBool = false;

	BHE4_4.name += "BHE4_4";
	BHE4_4.tag += "<td id=\"bhe44\" class=\"dato\">";
	BHE4_4.unit += "°C";
	BHE4_4.isBool = false;

	//ON OFF

	HEAT_PUMP.name += "HEAT_PUMP";
	HEAT_PUMP.tag += "<td id=\"heatPump\" class=\"dato\">";
	HEAT_PUMP.isBool = true;

	KF1.name += "KF1";
	KF1.tag += "<td id=\"coaxialBHEvalve\" class=\"dato\">";
	KF1.isBool = true;

	KF2.name += "KF2";
	KF2.tag += "<td id=\"helixBHEvalve\" class=\"dato\">";
	KF2.isBool = true;

	KF3.name += "KF3";
	KF3.tag += "<td id=\"singleBHEvalve\" class=\"dato\">";
	KF3.isBool = true;

	KF4.name += "KF4";
	KF4.tag += "<td id=\"pilotBHEvalve\" class=\"dato\">";
	KF4.isBool = true;

	RES_TANK.name += "RES_TANK";
	RES_TANK.tag += "<td id=\"tankAux\"  class=\"dato\">";
	RES_TANK.isBool = true;

	geoVars.Add(T_HP1);
	geoVars.Add(T_HP2);
	geoVars.Add(T_AMB1);
	geoVars.Add(T_GR1);
	geoVars.Add(T_3V1);
	geoVars.Add(T_3V2);
	geoVars.Add(T_3V3);
	geoVars.Add(T_3V4);
	geoVars.Add(FLOW1);
	geoVars.Add(PRES1);

	//VARIABLES BHE1

	geoVars.Add(BHE1_1);
	geoVars.Add(BHE1_2);
	geoVars.Add(BHE1_3);
	geoVars.Add(BHE1_4);
	//VARIABLES BHE2

	geoVars.Add(BHE2_1);
	geoVars.Add(BHE2_2);
	geoVars.Add(BHE2_3);
	geoVars.Add(BHE2_4);

	//VARIABLES BHE3

	geoVars.Add(BHE3_1);
	geoVars.Add(BHE3_2);
	geoVars.Add(BHE3_3);
	geoVars.Add(BHE3_4);

	//VARIABLES BHE4

	geoVars.Add(BHE4_1);
	geoVars.Add(BHE4_2);
	geoVars.Add(BHE4_3);
	geoVars.Add(BHE4_4);

	//VARIABLES ON/OFF
	geoVars.Add(HEAT_PUMP);
	geoVars.Add(KF1);
	geoVars.Add(KF2);
	geoVars.Add(KF3);
	geoVars.Add(KF4);
	geoVars.Add(RES_TANK);

	for (int i = 0; i < geoVars.Num(); i++)
	{
		geoVars[i].value = std::numeric_limits<float>::min();
	}
}