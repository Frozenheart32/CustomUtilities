// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LODFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMLODGENERATIONPLUGIN_API ULODFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Editor|LODGeneration")
	static bool TryModifyLODs(UObject* AssetInstance, const int32 LODCount = 3);
};
