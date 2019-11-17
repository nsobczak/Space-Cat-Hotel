#include "Engineer.h"

AEngineer::AEngineer()
{
	WNature = EWorkerNature::FWN_ENGINEER;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEngineer::BeginPlay()
{
	Super::BeginPlay();

}

void AEngineer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}