#include "Mine.h"

int32 AMine::MineCount = 0;

AMine::AMine()
{
	FNature = EFacilityNature::FFN_MINE;
	DistToBeSeenInside = 200.f;

	CostOxygenToSpawn = 50;
	CostRawToSpawn = 0;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMine::BeginPlay()
{
	Super::BeginPlay();

	AMine::MineCount++;
}

void AMine::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}