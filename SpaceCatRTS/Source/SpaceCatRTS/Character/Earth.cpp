#include "Earth.h"
#include "Character/Harvester.h"
#include "Character/Engineer.h"
#include "Engine/World.h"

AEarth::AEarth()
{
	FNature = EFacilityNature::FFN_EARTH;
	DistToBeSeenInside = 500.f;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEarth::BeginPlay()
{
	Super::BeginPlay();

}

void AEarth::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

AHarvester* AEarth::SpawnHarvester()
{
	//TODO: check oxygen value + max harvester count value
	if (BPHarvester)
	{
		FVector NewLocation = GetActorLocation() + FVector(0.f, 500.f, 100.f);

		// Spawn the new actor (Using GetClass() instead of AMySpawner so that if someone derives a new class  
		// from AMySpawner we spawn an instance of that class instead)  
		return GetWorld()->SpawnActor<AHarvester>(BPHarvester, NewLocation, FRotator::ZeroRotator);
	}
	else
	{
		return nullptr;
	}
}

AEngineer* AEarth::SpawnEngineer()
{
	//TODO: check oxygen value + max engineer count value
	if (BPEngineer)
	{
		FVector NewLocation = GetActorLocation() + FVector(0.f, 500.f, 100.f);
		return GetWorld()->SpawnActor<AEngineer>(BPEngineer, NewLocation, FRotator::ZeroRotator);
	}
	else
	{
		return nullptr;
	}
}