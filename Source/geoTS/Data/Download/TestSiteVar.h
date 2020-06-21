#pragma once
#pragma once

#include "CoreMinimal.h"

#include "TestSiteVar.generated.h"

USTRUCT(Blueprintable)
struct GEOTS_API FTestSiteVar
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestSite)
		FString tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestSite)
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestSite)
		FString unit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestSite)
		bool isBool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TestSite)
		float value;
};
