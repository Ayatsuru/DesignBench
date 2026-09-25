// Fill out your copyright notice in the Description page of Project Settings.

#include "EntityDatabaseEditorSubsystem.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "EditorValidatorSubsystem.h"
#include "Modules/ModuleManager.h"
#include "Entities/EntityDefinition.h"
#include "GameplayTagsManager.h"
#include "Editor.h"
#include "Engine/AssetManager.h"



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

TArray<UEntityDefinition*> UEntityDatabaseEditorSubsystem::GetEntitiesMatchingQuery(const FGameplayTagQuery& Query) const
{
	if (Query.IsEmpty())
	{
		return GetAllEntities();
	}

	TArray<UEntityDefinition*> Result;
	for (const TObjectPtr<UEntityDefinition>& EntityPtr : EntityDefinitions)
	{
		if (Query.Matches(EntityPtr->EntityTags))
			Result.Add(EntityPtr.Get());
	}

	return Result;
}

FGameplayTagContainer UEntityDatabaseEditorSubsystem::GetEntityTags() const
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
	return GameplayTagsManager.RequestGameplayTagChildren(GetEntityTagFromName(FName(TEXT("Entity"))));
}
FGameplayTag UEntityDatabaseEditorSubsystem::GetEntityTagFromName(FName TagName) const
{
	return FGameplayTag::RequestGameplayTag(TagName, false);
}

void UEntityDatabaseEditorSubsystem::ValidateEntityDatabase()
{
	TArray<FAssetData> AssetData;
	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
	FARFilter Filter;
	Filter.ClassPaths.Add(UEntityDefinition::StaticClass()->GetClassPathName());
	Filter.PackagePaths.Add(FName(TEXT("/Game")));
	Filter.bRecursiveClasses = true;
	Filter.bRecursivePaths = true;
	AssetRegistry.GetAssets(Filter, AssetData);

	FValidateAssetsSettings Settings;
	FValidateAssetsResults Results;
	UEditorValidatorSubsystem* ValidatorSubsystem = GEditor->GetEditorSubsystem<UEditorValidatorSubsystem>();
	if(ValidatorSubsystem)
		ValidatorSubsystem->ValidateAssetsWithSettings(AssetData, Settings, Results);
}