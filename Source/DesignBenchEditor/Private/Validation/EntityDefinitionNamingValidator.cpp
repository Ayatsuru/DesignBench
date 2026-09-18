#include "Validation/EntityDefinitionNamingValidator.h"
#include "Entities/EntityDefinition.h"

bool UEntityDefinitionNamingValidator::CanValidateAsset_Implementation(const FAssetData& InAssetData,UObject* InAsset, FDataValidationContext& Context) const
{
    return InAsset && InAsset->IsA<UEntityDefinition>();
}

EDataValidationResult UEntityDefinitionNamingValidator::ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& Context)
{
    if (!InAsset->GetName().StartsWith(TEXT("DA_Entity_")))
    {
        AssetFails(InAsset, FText::FromString(TEXT("Entity Data Assets must be named as follow : DA_Entity_* .")));
        return EDataValidationResult::Invalid;
    }
    AssetPasses(InAsset);
    return EDataValidationResult::Valid;
}