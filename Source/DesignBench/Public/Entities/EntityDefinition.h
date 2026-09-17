// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Misc/DataValidation.h"
#include "EntityDefinition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DESIGNBENCH_API UEntityDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

#if WITH_EDITOR
	virtual EDataValidationResult  IsDataValid(FDataValidationContext& context) const override;
#endif

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity")
	FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity")
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity")
	FGameplayTagContainer EntityTags;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity")
	TSoftClassPtr<AActor> ActorClass;
	
};
