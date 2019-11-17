#include "Harvester.h"

AHarvester::AHarvester()
{
	WNature = EWorkerNature::FWN_HARVESTER;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AHarvester::BeginPlay()
{
	Super::BeginPlay();

}

void AHarvester::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}