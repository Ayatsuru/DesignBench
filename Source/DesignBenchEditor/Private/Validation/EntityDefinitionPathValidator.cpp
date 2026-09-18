#include "Validation/EntityDefinitionPathValidator.h"
#include "Entities/EntityDefinition.h"

bool UEntityDefinitionPathValidator::CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& Context) const
{
    return InAsset && InAsset->IsA<UEntityDefinition>();
}

EDataValidationResult UEntityDefinitionPathValidator::ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& Context)
{
    if (!InAssetData.GetObjectPathString().StartsWith(TEXT("/Game/DesignBench/Entities")))
    {
        AssetFails(InAsset, FText::FromString(TEXT("Entity Data Assets must be placed in DesignBench/Entities folder.")));
        return EDataValidationResult::Invalid;
    }
    AssetPasses(InAsset);
    return EDataValidationResult::Valid;
}