#pragma once

#include "CoreMinimal.h"
#include "EditorValidatorBase.h"
#include "EntityDefinitionPathValidator.generated.h"

UCLASS()
class UEntityDefinitionPathValidator : public UEditorValidatorBase
{
    GENERATED_BODY()

protected:

    virtual bool CanValidateAsset_Implementation( const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& Context) const override;

    virtual EDataValidationResult ValidateLoadedAsset_Implementation( const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& Context) override;
};