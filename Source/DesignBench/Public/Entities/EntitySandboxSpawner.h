#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EntitySandboxSpawner.generated.h"

UCLASS()
class DESIGNBENCH_API AEntitySandboxSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEntitySandboxSpawner();

	UFUNCTION(BlueprintCallable, Category = "DesignBench|Sandbox")
	AActor* SpawnEntity(UEntityDefinition* EntityDefinition);
	UFUNCTION(BlueprintCallable, Category = "DesignBench|Sandbox")
	void SnapCurrentActorToGround();

private:
	AActor* CurrentSpawnedActor;
	UEntityDefinition* CurrentSpawnedEnitityDefinition;
	void SnapActorToGround();
};
