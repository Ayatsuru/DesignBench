#include "Entities/EntitySandboxSpawner.h"
#include "Entities/EntityDefinition.h"

AEntitySandboxSpawner::AEntitySandboxSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

AActor* AEntitySandboxSpawner::SpawnEntity(UEntityDefinition* EntityDefinition)
{
	if (IsValid(CurrentSpawnedActor))
	{
		CurrentSpawnedActor->Destroy();
		CurrentSpawnedActor = nullptr;
	}
	if (!IsValid(EntityDefinition))
	{
		UE_LOG(LogTemp, Display, TEXT("SpawnEntity called with an invalid EntityDefinition."));
		return nullptr;
	}
	CurrentSpawnedEnitityDefinition = EntityDefinition;

	if (EntityDefinition->ActorClass.IsNull())
	{
		UE_LOG(LogTemp, Display, TEXT("EntityDefinition has no class reference."));
		return nullptr;
	}

	TSubclassOf<AActor> ClassToSpawn = EntityDefinition->ActorClass.LoadSynchronous();

	if (!ClassToSpawn)
	{
		UE_LOG(LogTemp, Display, TEXT("EntityDefinition class could not be loaded."));
		return nullptr;
	}

	const FTransform SpawnerTransform = GetActorTransform();
	FActorSpawnParameters SpawnParameters;
	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogTemp, Display, TEXT("EntitySandboxSpawner has no valid World."));
		return nullptr;
	}

	CurrentSpawnedActor = World->SpawnActor<AActor>(ClassToSpawn, SpawnerTransform, SpawnParameters);

	SnapActorToGround();

	return CurrentSpawnedActor;

}

void AEntitySandboxSpawner::SnapActorToGround()
{
	if (IsValid(CurrentSpawnedActor))
	{
		FVector ActorOrigin;
		FVector ActorBoxExtent;
		CurrentSpawnedActor->GetActorBounds(false, ActorOrigin, ActorBoxExtent);

		FHitResult HitResult;
		FVector StartLocation = ActorOrigin + FVector(0.f, 0.f, ActorBoxExtent.Z + 100.f);
		FVector EndLocation = ActorOrigin - FVector(0.f, 0.f, ActorBoxExtent.Z + 1000.f);
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(CurrentSpawnedActor);
		bool bTraceHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, QueryParams);
		if (bTraceHit)
		{
			const float ActorBottomZ = ActorOrigin.Z - ActorBoxExtent.Z;
			const float ZOffset = HitResult.ImpactPoint.Z - ActorBottomZ;
			FVector NewLocation = CurrentSpawnedActor->GetActorLocation();
			NewLocation.Z += ZOffset;
			CurrentSpawnedActor->SetActorLocation(NewLocation);
		}
		
	}
}

// Blueprint callable function
void AEntitySandboxSpawner::SnapCurrentActorToGround()
{
	SnapActorToGround();
}