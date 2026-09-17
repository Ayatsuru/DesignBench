// Fill out your copyright notice in the Description page of Project Settings.


#include "Catalog/EntityCatalogSubsystem.h"
#include "Entities/EntityDefinition.h"
#include "Engine/AssetManager.h"

void UEntityCatalogSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	BuildCatalog();
}

void UEntityCatalogSubsystem::Deinitialize()
{
	EntityDefinitions.Empty();

	Super::Deinitialize();
}

const TArray<TObjectPtr<UEntityDefinition>>& UEntityCatalogSubsystem::GetAllEntities() const
{
	return EntityDefinitions;
}

void UEntityCatalogSubsystem::BuildCatalog()
{
	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<FPrimaryAssetId> EntityIds;
	const FPrimaryAssetType EntityDefinitionType(TEXT("EntityDefinition"));
	bool bFoundAssets = AssetManager.GetPrimaryAssetIdList(
		EntityDefinitionType,
		EntityIds
	);

	if (bFoundAssets)
	{
		FAssetData AssetData;
		for (const FPrimaryAssetId& EntityId : EntityIds)
		{
			if (!AssetManager.GetPrimaryAssetData(EntityId, AssetData))
				continue;

			UEntityDefinition* EntityData = Cast<UEntityDefinition>(AssetData.GetAsset());
			if (!EntityData)
				continue;

			UE_LOG(
				LogTemp,
				Display,
				TEXT("'\nName: %s\nDescription: %s\nActorClass: %s"),
				*EntityData->DisplayName.ToString(),
				*EntityData->Description.ToString(),
				*EntityData->ActorClass.ToSoftObjectPath().ToString()
			);

			EntityDefinitions.Add(EntityData);
		}
	}
}

TArray<UEntityDefinition*> UEntityCatalogSubsystem::GetAllEntitiesForBlueprint() const
{
	TArray<UEntityDefinition*> Result;
	for (const TObjectPtr<UEntityDefinition>& EntityPtr : EntityDefinitions)
	{
		Result.Add(EntityPtr.Get());
	}

	return Result;
}


TArray<UEntityDefinition*> UEntityCatalogSubsystem::GetEntitiesMatchingQuery(const FGameplayTagQuery& TagQuery) const
{
	TArray<UEntityDefinition*> Result;
	for (const TObjectPtr<UEntityDefinition>& EntityPtr : EntityDefinitions)
	{
		if (EntityPtr->EntityTags.MatchesQuery(TagQuery))
		{
			Result.Add(EntityPtr.Get());
		}
	}
	return Result;
}

TArray<UEntityDefinition*> UEntityCatalogSubsystem::SearchEntitiesByName(const FString& Name) const
{
	TArray<UEntityDefinition*> Result;
	for (const TObjectPtr<UEntityDefinition>& EntityPtr : EntityDefinitions)
	{
		if (EntityPtr->DisplayName.ToString().Contains(Name))
		{
			Result.Add(EntityPtr.Get());
		}
	}
	return Result;
}