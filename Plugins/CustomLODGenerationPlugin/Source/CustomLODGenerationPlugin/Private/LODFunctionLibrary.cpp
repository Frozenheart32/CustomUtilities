// Fill out your copyright notice in the Description page of Project Settings.


#include "LODFunctionLibrary.h"

#include "EditorStaticMeshLibrary.h"


bool ULODFunctionLibrary::TryModifyLODs(UObject* AssetInstance, const int32 LODCount)
{
	bool Result = false;
	
	if(!AssetInstance || LODCount < 1) return Result;

	if(auto Mesh = Cast<UStaticMesh>(AssetInstance))
	{
		Result = true;
		TArray<FEditorScriptingMeshReductionSettings> ReductionSettings;

		FEditorScriptingMeshReductionSettings Settings;

		//Set LOD 0;
		Settings.PercentTriangles = 1;
		Settings.ScreenSize = 0.9f;
		ReductionSettings.Add(Settings);


		if(LODCount > 1)
		{
			for (int32 i = 2; i <= LODCount; i++)
			{
				const float Percent = 1 / i;
				Settings.PercentTriangles = Percent;
				Settings.ScreenSize = Percent;
				ReductionSettings.Add(Settings);
			}
		}

		FEditorScriptingMeshReductionOptions Options;
		Options.ReductionSettings = ReductionSettings;

		UEditorStaticMeshLibrary::SetLods(Mesh, Options);

		AssetInstance->MarkPackageDirty();
	}

	return Result;
}
