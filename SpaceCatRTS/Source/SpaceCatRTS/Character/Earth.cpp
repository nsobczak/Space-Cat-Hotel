#include "Earth.h"
#include "UObject/ConstructorHelpers.h"
#include "Character/Harvester.h"
#include "Character/Engineer.h"
#include "PlayerController/SpaceCatRTSPlayerController.h"
#include "Engine/World.h"

AEarth::AEarth()
{
	FNature = EFacilityNature::FFN_EARTH;
	DistToBeSeenInside = 500.f;

	// Default blueprints
	static ConstructorHelpers::FClassFinder<AHarvester> harvesterBP(TEXT("/Game/Selectable/Worker/BPHarvester"));
	if (harvesterBP.Succeeded())
	{
		BPHarvesterToSpawn = harvesterBP.Class;
	}
	static ConstructorHelpers::FClassFinder<AEngineer> engineerBP(TEXT("/Game/Selectable/Worker/BPEngineer"));
	if (engineerBP.Succeeded())
	{
		BPEngineerToSpawn = engineerBP.Class;
	}

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
	if (BPHarvesterToSpawn)
	{
		if (BPHarvesterToSpawn && PC && BPHarvesterToSpawn.GetDefaultObject()
			&& PC->GetOxygenVal() >= BPHarvesterToSpawn.GetDefaultObject()->CostOxygenToSpawn
			&&  PC->GetOxygenVal() >= BPHarvesterToSpawn.GetDefaultObject()->CostRawToSpawn)
		{
			FVector NewLocation = GetActorLocation() + FVector(0.f, 500.f, 100.f);
			if (AHarvester* const newHarvester = GetWorld()->SpawnActor<AHarvester>(BPHarvesterToSpawn, NewLocation, FRotator::ZeroRotator))
			{
				PC->AddOxygenVal(-BPHarvesterToSpawn.GetDefaultObject()->CostOxygenToSpawn);
				PC->AddRawMatVal(-BPHarvesterToSpawn.GetDefaultObject()->CostRawToSpawn);
				return newHarvester;
			}
		}
	}
	return nullptr;
}

AEngineer* AEarth::SpawnEngineer()
{
	if (BPEngineerToSpawn && PC && BPEngineerToSpawn.GetDefaultObject()
		&& PC->GetOxygenVal() >= BPEngineerToSpawn.GetDefaultObject()->CostOxygenToSpawn
		&& PC->GetRawMatVal() >= BPEngineerToSpawn.GetDefaultObject()->CostRawToSpawn)
	{
		FVector NewLocation = GetActorLocation() + FVector(0.f, 500.f, 100.f);
		if (AEngineer* const newEngineer = GetWorld()->SpawnActor<AEngineer>(BPEngineerToSpawn, NewLocation, FRotator::ZeroRotator))
		{
			PC->AddOxygenVal(-BPEngineerToSpawn.GetDefaultObject()->CostOxygenToSpawn);
			PC->AddRawMatVal(-BPEngineerToSpawn.GetDefaultObject()->CostRawToSpawn);
			return newEngineer;
		}
	}
	return nullptr;
}