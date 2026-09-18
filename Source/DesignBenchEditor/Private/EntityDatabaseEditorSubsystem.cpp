// Fill out your copyright notice in the Description page of Project Settings.

#include "Entities/EntityDefinition.h"
#include "Engine/AssetManager.h"
#include "EntityDatabaseEditorSubsystem.h"


void UEntityDatabaseEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}
void UEntityDatabaseEditorSubsystem::Deinitialize()
{
	EntityDefinitions.Empty();
	Super::Deinitialize();
}

void UEntityDatabaseEditorSubsystem::BuildDatabase()
{

	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<FPrimaryAssetId> AssetIds;
	const FPrimaryAssetType EntityType(TEXT("EntityDefinition"));
	const bool bFoundAssets = AssetManager.GetPrimaryAssetIdList(EntityType, AssetIds);
	if (bFoundAssets)
	{
		FAssetData AssetData;
		for (const FPrimaryAssetId& AssetId : AssetIds)
		{
			if (!AssetManager.GetPrimaryAssetData(AssetId, AssetData))
				continue;
			UEntityDefinition* EntityData = Cast<UEntityDefinition>(AssetData.GetAsset());
			if (!EntityData)
				continue;
			
			UE_LOG(
				LogTemp,
				Display,
				TEXT("%s"),
				*EntityData->DisplayName.ToString()
			);

			EntityDefinitions.Add(EntityData);
		}
		
	}
}

void UEntityDatabaseEditorSubsystem::RefreshDatabase()
{
	EntityDefinitions.Empty();
	BuildDatabase();
}

TArray<UEntityDefinition*> UEntityDatabaseEditorSubsystem::GetAllEntities() const
{
	TArray<UEntityDefinition*> Result;
	for (const TObjectPtr<UEntityDefinition>& EntityPtr : EntityDefinitions)
	{
		Result.Add(EntityPtr.Get());
	}

	return Result;
}