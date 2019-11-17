#include "Facility.h"

AFacility::AFacility()
{
	SNature = ESelectableNature::FSN_FACILITY;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AFacility::BeginPlay()
{
	Super::BeginPlay();

}

void AFacility::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}