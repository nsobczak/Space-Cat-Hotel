#include "Worker.h"

AWorker::AWorker()
{
	SNature = ESelectableNature::FSN_WORKER;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CostRawToSpawn = 0;
}

void AWorker::BeginPlay()
{
	Super::BeginPlay();
}

void AWorker::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AWorker::DoNothing()
{
	bIsBuilding = false;
}