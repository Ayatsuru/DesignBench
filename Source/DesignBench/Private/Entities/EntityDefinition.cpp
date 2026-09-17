// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/EntityDefinition.h"

#if WITH_EDITOR
EDataValidationResult UEntityDefinition::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (DisplayName.IsEmpty())
	{
		Context.AddError(FText::FromString(TEXT("DisplayName must be assigned.")));
		Result = EDataValidationResult::Invalid;
	}
	if (ActorClass.IsNull())
	{
		Context.AddError(FText::FromString(TEXT("ActorClass must be assigned.")));
		Result = EDataValidationResult::Invalid;
	}
	if (EntityTags.IsEmpty())
	{
		Context.AddError(FText::FromString(TEXT("EntityTags must have at least one tag.")));
		Result = EDataValidationResult::Invalid;
	}
	FGameplayTag TypeTag = FGameplayTag::RequestGameplayTag(FName(TEXT("Entity.Type")));
	if (!EntityTags.HasTag(TypeTag))
	{
		Context.AddError(FText::FromString(TEXT("EntityTags must contain at least one Entity.Type.* tag.")));
		Result = EDataValidationResult::Invalid;
	}
	if (Description.IsEmpty())
	{
		Context.AddWarning(FText::FromString(TEXT("Description is empty.")));
	}
	return Result;
}
#endif