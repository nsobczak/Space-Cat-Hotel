#include "Worker.h"

AWorker::AWorker()
{
	SNature = ESelectableNature::FSN_WORKER;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AWorker::BeginPlay()
{
	Super::BeginPlay();
}

void AWorker::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}