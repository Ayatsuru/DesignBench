// Fill out your copyright notice in the Description page of Project Settings.

#include "Tests/EntityDiscoveryTestActor.h"
#include "Entities/EntityDefinition.h"
#include "Engine/AssetManager.h"

// Sets default values
AEntityDiscoveryTestActor::AEntityDiscoveryTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEntityDiscoveryTestActor::BeginPlay()
{
    Super::BeginPlay();

    UAssetManager& AssetManager = UAssetManager::Get();

    const FPrimaryAssetType EntityDefinitionType(TEXT("EntityDefinition"));

    TArray<FPrimaryAssetId> EntityIds;

    const bool bFoundAssets = AssetManager.GetPrimaryAssetIdList(
        EntityDefinitionType,
        EntityIds,
        EAssetManagerFilter::Default
    );


    UE_LOG(
        LogTemp,
        Display,
        TEXT("DesignBench: Found %d EntityDefinitions."),
        EntityIds.Num()
    );

    FAssetData AssetData;
    if (bFoundAssets)
    {
        for (const FPrimaryAssetId& EntityId : EntityIds)
        {
            if(!AssetManager.GetPrimaryAssetData(EntityId, AssetData))
            {
                continue;
            }

            UE_LOG(
                LogTemp,
                Display,
                TEXT(" - %s"),
                *EntityId.ToString()
            );

            UObject* LoadedAsset = AssetData.GetAsset();
            UEntityDefinition* EntityData = Cast<UEntityDefinition>(LoadedAsset);

            if (!EntityData)
            {
                continue;
            }

            UE_LOG(
                LogTemp,
                Display,
                TEXT(" DisplayName: %s \n Description: %s \n ActorClass: %s\n EntityTags:"),
                *EntityData->DisplayName.ToString(),
                *EntityData->Description.ToString(),
                *EntityData->ActorClass.ToSoftObjectPath().ToString()
            );
            for (int i = 0; i < EntityData->EntityTags.Num(); i++)
            {
                UE_LOG(
                    LogTemp,
                    Display,
                    TEXT(" - %s"),
                    *EntityData->EntityTags.GetByIndex(i).ToString()
                );
            }

        }
    }

    

    


    
}

// Called every frame
void AEntityDiscoveryTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

