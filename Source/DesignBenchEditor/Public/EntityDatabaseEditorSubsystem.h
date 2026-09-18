#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "EntityDatabaseEditorSubsystem.generated.h"

class UEntityDefinition;


/**
 * Editor equivalent of the runtime Entity Catalog.
 * Stores and exposes EntityDefinitions for designer-facing editor tools.
 */
UCLASS()
class DESIGNBENCHEDITOR_API UEntityDatabaseEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	UFUNCTION(BlueprintPure, Category = "DesignBenchEditor|Entities", meta = (ReturnDisplayName = "Entities"))
	TArray<UEntityDefinition*> GetAllEntities() const;
	UFUNCTION(BlueprintCallable, Category = "DesignBenchEditor|Entities")
	void RefreshDatabase();


private:
	void BuildDatabase();
	UPROPERTY()
	TArray<TObjectPtr<UEntityDefinition>> EntityDefinitions;
};
