// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "GenerateLODsCommandlet.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMLODGENERATIONPLUGIN_API UGenerateLODsCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	
	virtual int32 Main(const FString& Params) override;

private:
	
	void ProcessAssets(const TArray<FString>& RootDirectories, const int32 LODCount = 3);
	bool Execute(UObject* AssetInstance, const int32& LODCount);
	void SaveAsset(UObject* AssetInstance);
};
