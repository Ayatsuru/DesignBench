// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EntityCatalogSubsystem.generated.h"


class UEntityDefinition;

/**
 * 
 */
UCLASS()
class DESIGNBENCH_API UEntityCatalogSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	const TArray<TObjectPtr<UEntityDefinition>>& GetAllEntities() const;
	
	// Blueprint API
	UFUNCTION(BlueprintPure, Category = "DesignBench|Entities")
	TArray<UEntityDefinition*> GetAllEntitiesForBlueprint() const;
	UFUNCTION(BlueprintPure, Category = "Entity|Entities")
	TArray<UEntityDefinition*> GetEntitiesMatchingQuery(const FGameplayTagQuery& TagQuery) const;
	
	TArray<UEntityDefinition*> FindEntityById(FPrimaryAssetId AssetId) const;
	UFUNCTION(BlueprintPure, Category = "Entity|Entities")
	TArray<UEntityDefinition*> SearchEntitiesByName(const FString& Name) const;

	

private:
	void BuildCatalog();
	UPROPERTY()
	TArray<TObjectPtr<UEntityDefinition>> EntityDefinitions;
};
