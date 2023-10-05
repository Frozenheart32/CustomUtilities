// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerateLODsCommandlet.h"

#include "LODFunctionLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Kismet/KismetStringLibrary.h"

int32 UGenerateLODsCommandlet::Main(const FString& Params)
{
	TArray<FString> Tokens;
	TArray<FString> Switches;
	TMap<FString, FString> ParamsMap;

	ParseCommandLine(*Params, Tokens, Switches, ParamsMap);
	//-run=GenerateLODs -GenerateLOD token1 token2 token3
	//-run=GenerateLODs -GenerateLOD token1 token2 token3 -LODCount=3

	if(Switches.Contains(TEXT("GenerateLOD")) && Tokens.Num() > 0)
	{
		const FString LODCountKey{"LODCount"};
		if(ParamsMap.Contains(LODCountKey))
		{
			ProcessAssets(Tokens, UKismetStringLibrary::Conv_StringToInt(ParamsMap[LODCountKey]));
		}
		else
		{
			ProcessAssets(Tokens);
		}
	}

	return 0;
}

void UGenerateLODsCommandlet::ProcessAssets(const TArray<FString>& RootDirectories, const int32 LODCount)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);

	AssetRegistryModule.Get().SearchAllAssets(true);

	const FString ClassName = TEXT("StaticMesh");
	TArray<FAssetData> AssetList;
	AssetRegistryModule.Get().GetAssetsByClass(*ClassName, AssetList, true);

	for (const auto& AssetData : AssetList)
	{
		for (const auto& RootDirectory : RootDirectories)
		{
			if(AssetData.ObjectPath.ToString().StartsWith(RootDirectory, ESearchCase::IgnoreCase))
			{
				UObject* AssetInstance = AssetData.GetAsset();

				const bool Result = Execute(AssetInstance, LODCount);

				if(Result)
					SaveAsset(AssetInstance);
			}
		} 
	} 
}

bool UGenerateLODsCommandlet::Execute(UObject* AssetInstance, const int32& LODCount)
{
	return ULODFunctionLibrary::TryModifyLODs(AssetInstance, LODCount);
}

void UGenerateLODsCommandlet::SaveAsset(UObject* AssetInstance)
{
	if(!AssetInstance) return;

	//Package = File (.uasset)
	if(UPackage* Package = AssetInstance->GetPackage())
	{
		if(Package->IsDirty())
		{
			const FString PackageName = FPackageName::LongPackageNameToFilename(Package->GetPathName(),
				FPackageName::GetAssetPackageExtension());

			UE_LOG(LogClass, Log, TEXT("Saving asset to:  %s"), *PackageName);

			if(Package->SavePackage(Package, AssetInstance, RF_Standalone, *PackageName, GLog))
			{
				UE_LOG(LogClass, Log, TEXT("Done."));
			}
			else
			{
				UE_LOG(LogClass, Log, TEXT("Can't save asset!"));
			}
		}
	}
}
